set(MURMUR_SOURCE
        #src/murmur/BonjourServer.cpp
        #src/murmur/BonjourServer.h
        src/murmur/Cert.cpp
        #        src/murmur/DBus.cpp
        #        src/murmur/DBus.h
        src/murmur/main.cpp
        src/murmur/Messages.cpp
        src/murmur/Meta.cpp
        src/murmur/Meta.h
        src/murmur/murmur_pch.h
        #        src/murmur/MurmurGRPCImpl.cpp
        #        src/murmur/MurmurGRPCImpl.h
        src/murmur/MurmurI.h
        #        src/murmur/MurmurIce.cpp
        #        src/murmur/MurmurIce.h
        #        src/murmur/MurmurIceWrapper.cpp
        src/murmur/PBKDF2.cpp
        src/murmur/PBKDF2.h
        src/murmur/Register.cpp
        src/murmur/RPC.cpp
        src/murmur/Server.cpp
        src/murmur/Server.h
        src/murmur/ServerDB.cpp
        src/murmur/ServerDB.h
        src/murmur/ServerUser.cpp
        src/murmur/ServerUser.h
        src/murmur/UnixMurmur.cpp
        src/murmur/UnixMurmur.h
        #        src/murmur_grpcwrapper_protoc_plugin/main.cpp
        )

if(WIN32)
    list(APPEND MURMUR_SOURCE src/murmur/About.cpp src/murmur/About.h src/murmur/Tray.cpp src/murmur/Tray.h)
endif()

add_executable(RmMurmur ${SHARED_SOURCE} ${SHARED_HEADERS} ${SPEEX_SOURCES})
target_link_libraries(RmShared PRIVATE Qt5::Gui Qt5::Network Qt5::Widgets Qt5::DBus Qt5::Xml Qt5::Sql crypto ssl sndfile)
target_include_directories(RmShared
        PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}/src/>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/>
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src/
        )