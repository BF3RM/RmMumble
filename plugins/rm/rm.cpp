/*
* Developed as part of the Project Reality mod for BF3/Venice Unleashed.
* Jury Verrigni - Snaiperskaya
*/

#define _WINSOCKAPI_    // stops windows.h including winsock.h
#include "../mumble_plugin_win32.h"
#include <fstream>
#include <thread>
#include <chrono>

//#define PR_DEBUG

#ifdef PR_DEBUG
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
static SOCKET* UdpSocket = nullptr;
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
    procptr_t SquadState = ResolveChain();

    if (!SquadState) {
        return false;
    }

    procptr_t SquadLeaderState = SquadState + 0x4;

    procptr_t FactionState = SquadState - 0x150;

    unsigned char IsSquadLeader = 0;
    unsigned char SquadId = 0;
    unsigned char FactionId = 0;

    peekProc(SquadState, &SquadId, sizeof(char));
    peekProc(SquadLeaderState, &IsSquadLeader, sizeof(char));
    peekProc(FactionState, &FactionId, sizeof(char));

    for (int i=0;i<3;i++) {
        avatar_pos[i] = avatar_front[i] = avatar_top[i] = camera_pos[i] = camera_front[i] = camera_top[i] = -1.0f;
    }

    // Boolean values to check if game addresses retrieval is successful and if the player is in-game
    bool ok;
    uint8_t state = 0;
    // Create containers to stuff our raw data into, so we can convert it to Mumble's coordinate system
    float avatar_pos_corrector[3], avatar_front_corrector[3], avatar_top_corrector[3];
    // Peekproc and assign game addresses to our containers, so we can retrieve positional data
    ok = peekProc(StatePtr, &state, 1) && // Magical state value: 1 when in-game and 0 when in main menu.
        peekProc(AvatarPosPtr, avatar_pos_corrector, 12) && // Avatar Position values (X, Z and Y, respectively).
        peekProc(AvatarFrontPtr, avatar_front_corrector, 12) && // Avatar Front Vector values (X, Z and Y, respectively).
        peekProc(AvatarTopPtr, avatar_top_corrector, 12); // Avatar Top Vector values (X, Z and Y, respectively).

    context = ((int)FactionId == 1 ? "US" : "RU");

    auto FactionString = std::to_string(FactionId);
    auto SquadString = std::to_string(SquadId);
    auto IsSquadLeaderString = std::to_string(IsSquadLeader);

    // Identity: Faction~~Squad~~SquadLeader
    std::stringstream IdentityStream;
    IdentityStream << FactionString << "~~"
                   << SquadString << "~~"
                   << IsSquadLeaderString;

    identity = StringToWString(IdentityStream.str());

    // This prevents the plugin from linking to the game in case something goes wrong during values retrieval from memory addresses.
    if (!ok) {
        return false;
    }

    if (state != STATE_IN_GAME && state != STATE_IN_MENU) { // If not in-game
        context.clear(); // Clear context
        identity.clear(); // Clear identity
        // Set vectors values to 0.
        for (int i=0;i<3;i++)
            avatar_pos[i] = avatar_front[i] = avatar_top[i] = camera_pos[i] =  camera_front[i] = camera_top[i] = 0.0f;
        return true; // This tells Mumble to ignore all vectors.
    }

    avatar_pos[0] = avatar_pos_corrector[0];
    avatar_pos[1] = avatar_pos_corrector[1];
    avatar_pos[2] = avatar_pos_corrector[2];

    avatar_front[0] = avatar_front_corrector[0];
    avatar_front[1] = avatar_front_corrector[1];
    avatar_front[2] = avatar_front_corrector[2];

    avatar_top[0] = avatar_top_corrector[0];
    avatar_top[1] = avatar_top_corrector[1];
    avatar_top[2] = avatar_top_corrector[2];

    // Flip our front vector
    for (int i=0;i<3;i++) {
        avatar_front[i] = -avatar_front[i];
    }

    // Convert from right to left handed
    avatar_pos[0] = -avatar_pos[0];
    avatar_front[0] = -avatar_front[0];
    avatar_top[0] = -avatar_top[0];

    for (int i=0;i<3;i++) {
        camera_pos[i] = avatar_pos[i];
        camera_front[i] = avatar_front[i];
        camera_top[i] = avatar_top[i];
    }

    //    send(server, buffer, sizeof(buffer), 0);
#ifdef PR_DEBUG
    if (UdpSocket != nullptr) {
        //Username~~Server~~Faction~~Squad~~IsSquadLeader
        memset(DebugString, '\0', sizeof(DebugString));

        int Offset = 0;
#define CPY(TEXT, SIZE) memcpy (&DebugString[Offset], TEXT, SIZE); Offset += SIZE;
#define SPACER() CPY("~~", 2)
#define COPY(TEXT, SIZE) CPY(TEXT, SIZE) SPACER()
        COPY("FetchMe", 7);
        COPY("FetchMe", 7);
        COPY(FactionString.c_str(), (int)FactionString.size());
        COPY(SquadString.c_str(), (int)SquadString.size());
        COPY(IsSquadLeaderString.c_str(), (int)IsSquadLeaderString.size());
#undef CPY
#undef SPACER
#undef COPY

        send(*UdpSocket, (const char*)&DebugString[0], sizeof(DebugString), 0);
    }
#endif

    return true;
}

static void InitSocket()
{
#ifdef PR_DEBUG
    if (UdpSocket == nullptr) {
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
            UdpSocket = new SOCKET(socket(ptr->ai_family, ptr->ai_socktype,
                ptr->ai_protocol));
            if (*UdpSocket == INVALID_SOCKET) {
                printf("socket failed with error: %ld\n", WSAGetLastError());
                WSACleanup();
                return;
            }

            connect(*UdpSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

            break;
        }
    }
#endif
}

static int trylock(const std::multimap<std::wstring, unsigned long long int> &pids) {
    if (!initialize(pids, L"vu.exe")) { // Retrieve game executable's memory address
        return false;
    }

    // Check if we can get meaningful data from i
    float apos[3], afront[3], atop[3], cpos[3], cfront[3], ctop[3];
    std::wstring sidentity;
    std::string scontext;

    if (fetch(apos, afront, atop, cpos, cfront, ctop, scontext, sidentity)) {
        InitSocket();
        return true;
    } else {
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
