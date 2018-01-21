// Copyright 2005-2018 The Mumble Developers. All rights reserved.
// Use of this source code is governed by a BSD-style license
// that can be found in the LICENSE file at the root of the
// Mumble source tree or at <https://www.mumble.info/LICENSE>.

/* Copyright (C) 2010-2011, Snares <snares@users.sourceforge.net>
   Copyright (C) 2005-2011, Thorvald Natvig <thorvald@natvig.com>
   Copyright (C) 2011, Ryan Austin <ryan@gameforcecenters.com>
   Copyright (C) 2012, Bojan Hartmann <bogie@bawki.de>

   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.
   - Neither the name of the Mumble Developers nor the names of its
     contributors may be used to endorse or promote products derived from this
     software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "../mumble_plugin_win32.h"
#include <fstream>
#include <thread>
#include <chrono>

// Magic ptrs
static procptr_t const StatePtr = 0x238ABDC;

// Vector ptrs
static procptr_t const AvatarPosPtr = 0x0238AB70;
static procptr_t const AvatarFrontPtr = 0x0238ABA0;
static procptr_t const AvatarTopPtr = 0x0238AB90;

// Context ptrs
static procptr_t const IpPortPtr = 0x0F87A0600;

// Identity ptrs
static procptr_t const UsernamePtr = 0x0A3B9B44;

enum state_values {
    STATE_UNKN = 0,
    STATE_LOADING = 1,
    STATE_IN_GAME = 2,
    STATE_IN_MENU = 3
};

// https://stackoverflow.com/questions/10737644/convert-const-char-to-wstring
std::wstring StringToWString(const std::string& str)
{
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
    std::wstring wstrTo( size_needed, 0 );
    MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
    return wstrTo;
}

static int fetch(float *avatar_pos, float *avatar_front, float *avatar_top, float *camera_pos, float *camera_front, float *camera_top, std::string &context, std::wstring &identity) {
    for (int i=0;i<3;i++) {
        avatar_pos[i] = avatar_front[i] = avatar_top[i] = camera_pos[i] = camera_front[i] = camera_top[i] = -1.0f;
    }

    // Boolean values to check if game addresses retrieval is successful and if the player is in-game
    bool ok, state;
        // Create containers to stuff our raw data into, so we can convert it to Mumble's coordinate system
    float avatar_pos_corrector[3], avatar_front_corrector[3], avatar_top_corrector[3];
    // Peekproc and assign game addresses to our containers, so we can retrieve positional data
    ok = peekProc(StatePtr, &state, 1) && // Magical state value: 1 when in-game and 0 when in main menu.
        peekProc(AvatarPosPtr, avatar_pos_corrector, 12) && // Avatar Position values (X, Z and Y, respectively).
        peekProc(AvatarFrontPtr, avatar_front_corrector, 12) && // Avatar Front Vector values (X, Z and Y, respectively).
        peekProc(AvatarTopPtr, avatar_top_corrector, 12); // Avatar Top Vector values (X, Z and Y, respectively).

    char ContextCharString[128];
    peekProc(IpPortPtr, ContextCharString, 128);

    char IdentityCharString[128];
    peekProc(UsernamePtr, IdentityCharString, 128);

    //context = ContextCharString;
    context = "asd";
    //identity = StringToWString(IdentityCharString);
    identity = L"";
    // This prevents the plugin from linking to the game in case something goes wrong during values retrieval from memory addresses.
    if (!ok) {
        return false;
    }

//    if (state == 2) state = 1;

    state = true;

    if (!state) { // If not in-game
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

    return true;
}

static SOCKET CreateSocket()
{
    return (SOCKET) 1;
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;

    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_DGRAM, 0);

    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // replace the ip with your futur server ip address. If server AND client are running on the same computer, you can use the local ip 127.0.0.1
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);

    connect(server, (SOCKADDR *)&addr, sizeof(addr));

    return server;
}

static void CloseSocket(SOCKET Sock)
{
    return;
    closesocket(Sock);
    WSACleanup();
}

static void SendSockMessage(SOCKET Sock, std::string String)
{
    return;
    send(Sock, String.c_str(), (int)String.length(), 0);
}

static int trylock(const std::multimap<std::wstring, unsigned long long int> &pids) {
    SOCKET sock = CreateSocket();

    SendSockMessage(sock, "Trylock Called\n");

    if (pids.count(L"vu.exe") < 3) {
        return false;
    }

    if (!initialize(pids, L"vu.exe")) { // Retrieve game executable's memory address
        return false;
        CloseSocket(sock);
    }

    SendSockMessage(sock, "Initialised.");

    // Check if we can get meaningful data from i
    float apos[3], afront[3], atop[3], cpos[3], cfront[3], ctop[3];
    std::wstring sidentity;
    std::string scontext;

    if (fetch(apos, afront, atop, cpos, cfront, ctop, scontext, sidentity)) {
        SendSockMessage(sock, "Fetched data.");
        CloseSocket(sock);
        return true;
    } else {
        SendSockMessage(sock, "Couldn't fetch any data.");
        generic_unlock();
        CloseSocket(sock);
        return false;
    }
}

static const std::wstring longdesc() {
    return std::wstring(L"Supports Battlefield 3 with context and identity support.");
}

static std::wstring description(L"Venice Unleashed - Realitymod");
static std::wstring shortname(L"VU Realitymod");

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
