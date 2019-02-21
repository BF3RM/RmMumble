/*
* Developed as part of the Project Reality mod for BF3/Venice Unleashed.
* Jury Verrigni - Snaiperskaya
*/

#define _WINSOCKAPI_    // stops windows.h including winsock.h

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>

#include "../mumble_plugin_win32.h"
#include <fstream>
#include <chrono>

//#define RM_DEBUG
#include <windows.h>
#include <ws2tcpip.h>

#define BUFLEN sizeof(float) * 3 * 3
#define PORT 55778

static SOCKET UdpSocket;
static HANDLE UdpThread = nullptr;
float PawnPosition[3];
float PawnFrontVector[3];
float PawnTopVector[3];

#ifdef RM_DEBUG
static unsigned char DebugString[64] = {'\0'};
#endif

// Magic ptrs
static procptr_t const StatePtr = 0x238ABDC;

// Vector ptrs
static procptr_t const AvatarPosPtr = 0x0238AB70;
static procptr_t const AvatarFrontPtr = 0x0238ABA0;
static procptr_t const AvatarTopPtr = 0x0238AB90;

// Context ptrs
static procptr_t const IpPortPtr = 0x0F87A0600;

// Offset Chain ptrs
static procptr_t const ChainOffset0 = 0x1EE3790;
static procptr_t const ChainOffset1 = 0xB4;
static procptr_t const ChainOffset2 = 0x1C;
static procptr_t const ChainOffset3 = 0xBC;
static procptr_t const ChainOffset4 = 0x46C;

enum state_values {
    STATE_UNKN = 0,
    STATE_LOADING = 1,
    STATE_IN_MENU = 2, // << Main menu/in game
    STATE_IN_GAME = 3 // << Before spawn
};

static procptr_t ResolveChain()
{
//    std::ofstream Stream("vu-pr.txt");
    procptr_t BasePtr = peekProcPtr(pModule + ChainOffset0);
    if (!BasePtr){
//        Stream << "No base ptr available" << std::endl;
//        Stream.close();
        return 0;
    }

//    Stream << "Base ptr: " << (void*) BasePtr << std::endl;

    procptr_t OffsettedPtr1 = peekProcPtr(BasePtr + ChainOffset1);
    if (!OffsettedPtr1) {
//        Stream << "Failed to fetch offset1 pointer" << std::endl;
//        Stream.close();
        return 0;
    }

//    Stream << "Offset 1: " << (void*) OffsettedPtr1 << std::endl;

    procptr_t OffsettedPtr2 = peekProcPtr(OffsettedPtr1 + ChainOffset2);
    if (!OffsettedPtr2) {
//        Stream << "Failed to fetch offset2 pointer" << std::endl;
//        Stream.close();
        return 0;
    }

//    Stream << "Offset 2: " << (void*) OffsettedPtr2 << std::endl;

    procptr_t OffsettedPtr3 = peekProcPtr(OffsettedPtr2 + ChainOffset3);
    if (!OffsettedPtr3) {
//        Stream << "Failed to fetch offset3 pointer" << std::endl;
//        Stream.close();
        return 0;
    }

//    Stream << "Offset 3: " << (void*) OffsettedPtr3 << std::endl;

    procptr_t OffsettedPtr4 = OffsettedPtr3 + ChainOffset4;

//    Stream << "Offset 4: " << (void*) OffsettedPtr4 << std::endl;

    return OffsettedPtr4;
}

// Offsets
static procptr_t const BaseOffset= 0x01F0B9CC;

/**
* "vu.exe" + 0x01F0B9CC => F9EFD790 <- Base offset
* F9EFD790 + 0x6E0 => E2E15EA8 <- Offset 1
* E2E15EA8 + 46C => E2E16314 <- Squad State // 0 No squad - 1 Alpha - 2 Bravo
* E2E16314 + 0x4 => E2E16318 <- Squad Leader State // 1 SL - 0 Non SL
* E2E16314 - 0x150 => Whatever <- Faction State // 1 US - 2 RU
*/

// https://stackoverflow.com/questions/10737644/convert-const-char-to-wstring
std::wstring StringToWString(const std::string& str)
{
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo( size_needed, 0 );
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

static int fetch(float *avatar_pos, float *avatar_front, float *avatar_top, float *camera_pos, float *camera_front, float *camera_top, std::string &context, std::wstring &identity) {
/*	PawnTopVector[0] = -0.f;
	PawnTopVector[1] = 1.f;
	PawnTopVector[2] = -0.f;

	PawnFrontVector[0] = 0.f;
	PawnFrontVector[1] = 0.f;
	PawnFrontVector[2] = 1.f;
	*/
	for (int I = 0; I < 3; I++)
	{
		avatar_top[I] = camera_top[I] = PawnTopVector[I];
		avatar_front[I] = camera_front[I] = -PawnFrontVector[I];
		avatar_pos[I] = camera_pos[I] = PawnPosition[I];

		// Flip our front vector
//		avatar_front[I] = -avatar_front[I];
	}

	avatar_top[0] = -avatar_top[0];
	avatar_front[0] = -avatar_front[0];
	avatar_pos[0] = -avatar_pos[0];

	identity = L"1~~1~~0";
	context = "";

	return true;
}

static void InitSocket()
{
#ifdef RM_DEBUG
    if (UdpSocket == NULL) {
        WSADATA WSAData;
        WSAStartup(MAKEWORD(2,0), &WSAData);
        struct addrinfo* Result = nullptr, hints;

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_protocol = IPPROTO_UDP;

        getaddrinfo("analytics.skayahack.uk", "5555", &hints, &Result);

        for (auto ptr = Result; ptr != NULL; ptr = ptr->ai_next) {

            // Create a SOCKET for connecting to server
            UdpSocket = SOCKET(socket(ptr->ai_family, ptr->ai_socktype,
                ptr->ai_protocol));
            if (UdpSocket == INVALID_SOCKET) {
                printf("socket failed with error: %ld\n", WSAGetLastError());
                WSACleanup();
                return;
            }

            connect(UdpSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

            break;
        }
    }
#endif
}

#ifdef RM_POSITIONAL_DEBUG
SOCKET RmDebugClient;
sockaddr_in RmDebugServer;

void InitPositionDebugSocket()
{
	memset((char *)&RmDebugServer, 0, sizeof(RmDebugServer));
	RmDebugServer.sin_family = AF_INET;
	RmDebugServer.sin_port = htons(55779);
	RmDebugServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	RmDebugClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}

void SendPositionDebug(const char* Data, size_t Len)
{
	if (sendto(RmDebugClient, Data, Len, 0, (struct sockaddr *) &RmDebugServer, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
}
#endif

bool RealityModInitServer()
{
	if (UdpSocket)
	{
		return true;
	}

	struct sockaddr_in server;
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return false;
	}

	//Create a socket
	if ((UdpSocket = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
		return false;
	}

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	//Bind
	if (bind(UdpSocket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		return false;
	}

	return true;
}

void RealityMod3dPositionHandler()
{
	char buf[BUFLEN];
	int slen, ReceivedLength;
	struct sockaddr_in si_other;
	slen = sizeof(si_other);
	while (1)
	{
		printf("Waiting for data...");
		fflush(stdout);

		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);

		//try to receive some data, this is a blocking call
		if ((ReceivedLength = recvfrom(UdpSocket, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			continue;
			//exit(EXIT_FAILURE);
		}

		constexpr auto Offset = sizeof(float) * 3;
		if (ReceivedLength >= Offset)
		{
			memcpy(PawnPosition, buf, Offset);
			memcpy(PawnFrontVector, buf + Offset, Offset);
			memcpy(PawnTopVector, buf + Offset * 2, Offset);
		}

#ifdef RM_POSITIONAL_DEBUG
		char Position[Offset + 4] = { '\0' };
		memcpy(Position, buf, Offset);
		const char* Name = "self";
		memcpy(Position + Offset, Name, 4);
		SendPositionDebug(Position, sizeof(Position));
#endif
	}

	closesocket(UdpSocket);
	WSACleanup();
}

static int trylock(const std::multimap<std::wstring, unsigned long long int> &pids) {
    if (!initialize(pids, L"vu.exe")) { // Retrieve game executable's memory address
        return false;
    }

    // Check if we can get meaningful data from i
	if (RealityModInitServer())
	{
		float* PawnPosition = nullptr;
		float* PawnFrontVector = nullptr;
		float* PawnTopVector = nullptr;

#ifdef RM_POSITIONAL_DEBUG
		InitPositionDebugSocket();
#endif

		if (!UdpThread)
		{
			UdpThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)RealityMod3dPositionHandler, nullptr, 0, nullptr);
		}
		return true;
	}
	else
	{
		generic_unlock();
		return false;
	}
}

static const std::wstring longdesc() {
    return std::wstring(L"Supports Battlefield 3 with context and identity support.");
}

static std::wstring description(L"RealityMod");
static std::wstring shortname(L"RealityMod");

static int trylock1() {
    return trylock(std::multimap<std::wstring, unsigned long long int>());
}

static MumblePlugin bf3plug = {
    MUMBLE_PLUGIN_MAGIC,
    description,
    shortname,
    NULL,
    NULL,
    trylock1,
    generic_unlock,
    longdesc,
    fetch
};

static MumblePlugin2 bf3plug2 = {
    MUMBLE_PLUGIN_MAGIC_2,
    MUMBLE_PLUGIN_VERSION,
    trylock
};

extern "C" MUMBLE_PLUGIN_EXPORT MumblePlugin *getMumblePlugin() {
    return &bf3plug;
}

extern "C" MUMBLE_PLUGIN_EXPORT MumblePlugin2 *getMumblePlugin2() {
    return &bf3plug2;
}
