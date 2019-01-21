/*
* Developed as part of the Project Reality mod for BF3/Venice Unleashed.
* Jury Verrigni - Snaiperskaya
*/

#define _WINSOCKAPI_    // stops windows.h including winsock.h
#define ASIO_STANDALONE 
#define _WEBSOCKETPP_CPP11_STL_

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>

#include "../mumble_plugin_win32.h"
#include <fstream>
#include <chrono>

//#define RM_DEBUG
#include <windows.h>
#include <ws2tcpip.h>

#include <websocketpp/config/asio_no_tls.hpp> 
#include <websocketpp/server.hpp>

#include <functional>
#include <set>
#include <mutex>

#define BUFLEN sizeof(float) * 3 * 3
#define UDPPORT 55779
#define WEBSOCKETPORT 55780

typedef websocketpp::server<websocketpp::config::asio> Server;

static SOCKET UdpSocket;
static HANDLE UdpThread = nullptr;
static Server WebSocketServer;

std::mutex ClientsMutex;
std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> Clients;

void OnWebOpen(websocketpp::connection_hdl Handler)
{
	ClientsMutex.lock();
	Clients.insert(Handler);
	ClientsMutex.unlock();
}

void OnWebClose(websocketpp::connection_hdl Handler)
{
	ClientsMutex.lock();
	Clients.erase(Handler);
	ClientsMutex.unlock();
}

static int fetch(float *avatar_pos, float *avatar_front, float *avatar_top, float *camera_pos, float *camera_front, float *camera_top, std::string &context, std::wstring &identity)
{
	return true;
}

static void WebsocketThread()
{
	WebSocketServer.run();
}

bool InitUdpServer()
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
	server.sin_port = htons(UDPPORT);

	//Bind
	if (bind(UdpSocket, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		return false;
	}

	return true;
}

bool InitWebsocketServer()
{
	if (WebSocketServer.is_listening())
	{
		return true;
	}

	try
	{
		WebSocketServer.set_access_channels(websocketpp::log::alevel::all);
		WebSocketServer.clear_access_channels(websocketpp::log::alevel::frame_payload);
		WebSocketServer.init_asio();
		WebSocketServer.set_open_handler(OnWebOpen);
		WebSocketServer.set_close_handler(OnWebClose);
		WebSocketServer.listen(WEBSOCKETPORT);
		WebSocketServer.start_accept();
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)WebsocketThread, nullptr, 0, nullptr);
	}
	catch (websocketpp::exception const& E)
	{
		std::cout << E.what() << std::endl;
	}
	catch (...)
	{
		return false;
	}

	return true;
}

static inline void RightTrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

void PositionHandler()
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

		ClientsMutex.lock();
		auto Payload = std::string(buf, BUFLEN);
		RightTrim(Payload);
		for (auto& Connection : Clients)
		{
			try
			{
				WebSocketServer.send(Connection, Payload, websocketpp::frame::opcode::binary);
			}
			catch (websocketpp::exception& e)
			{
				std::cout << e.m_msg << std::endl << e.what() << std::endl;
			}
		}
		ClientsMutex.unlock();
	}

	closesocket(UdpSocket);
	WSACleanup();
}

static int trylock(const std::multimap<std::wstring, unsigned long long int> &pids) {
	if (InitUdpServer() && InitWebsocketServer())
	{
		if (!UdpThread)
		{
			UdpThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)PositionHandler, nullptr, 0, nullptr);
		}
		return true;
	}
	else
	{
		generic_unlock();
		return false;
	}
}

static void unlock()
{
}

static const std::wstring longdesc() {
    return std::wstring(L"Does what the name says.");
}

static std::wstring description(L"Positional Audio Debug");
static std::wstring shortname(L"PositionalDebug");

static int trylock1() {
    return trylock(std::multimap<std::wstring, unsigned long long int>());
}

static MumblePlugin DebugPlugin = {
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

static MumblePlugin2 DebugPlugin2 = {
    MUMBLE_PLUGIN_MAGIC_2,
    MUMBLE_PLUGIN_VERSION,
    trylock
};

extern "C" MUMBLE_PLUGIN_EXPORT MumblePlugin *getMumblePlugin() {
    return &DebugPlugin;
}

extern "C" MUMBLE_PLUGIN_EXPORT MumblePlugin2 *getMumblePlugin2() {
    return &DebugPlugin2;
}
