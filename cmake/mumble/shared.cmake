#Qt5_DIR
find_package(Qt5 COMPONENTS Gui Network Widgets DBus Xml Sql Svg REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS thread)
link_directories(${Boost_LIBRARY_DIRS})

set(RM_OPENSSL_LIBS)
set(RM_OPENSSL_INCLUDE ${CMAKE_BINARY_DIR}/3rdparty)
set(SHARED_OBJS)

if(UNIX OR (WIN32 AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
        find_package(OpenSSL REQUIRED)
        set(RM_OPENSSL_LIBS ${OPENSSL_LIBRARIES})
        set(RM_OPENSSL_INCLUDE ${RM_OPENSSL_INCLUDE} ${OPENSSL_INCLUDE_DIR})
else()
        add_subdirectory(3rdparty/openssl)
        set(RM_OPENSSL_LIBS ssl crypto)
        set(RM_OPENSSL_INCLUDE ${RM_OPENSSL_INCLUDE} ${CMAKE_BINARY_DIR}/3rdparty/openssl/ssl ${CMAKE_BINARY_DIR}/3rdparty/openssl/crypto ${CMAKE_BINARY_DIR}/3rdparty/openssl/)
endif()
#include_directories(${CMAKE_BINARY_DIR}/3rdparty/libsndfile/src)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/)
include_directories(${CMAKE_SOURCE_DIR}/src/)
include_directories(${CMAKE_SOURCE_DIR}/src/mumble)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/arc4random-src/ ${CMAKE_SOURCE_DIR}/src/murmur)


set(SHARED_SOURCE
        src/ACL.cpp
        src/Ban.cpp
        src/Channel.cpp
        src/Connection.cpp
        src/CryptographicHash.cpp
        src/CryptographicRandom.cpp
        src/CryptState.cpp
        src/EnvUtils.cpp
        src/FFDHE.cpp
        src/Group.cpp
        src/HostAddress.cpp
        src/HTMLFilter.cpp
        src/License.cpp
        src/LogEmitter.cpp
        #        src/Net.cpp
        src/OSInfo.cpp
        src/PasswordGenerator.cpp
        src/PlatformCheck.cpp
        src/SelfSignedCertificate.cpp
        src/ServerAddress.cpp
        #src/ServerResolver_nosrv.cpp
        src/ServerResolver_qt5.cpp
        src/ServerResolverRecord.cpp
        src/ServerResolverPrivate.cpp
        src/SSL.cpp
        src/SSLCipherInfo.cpp
        src/SSLLocks.cpp
        src/Timer.cpp
        src/UnresolvedServerAddress.cpp
        src/User.cpp
        src/Version.cpp
        ${PROTO_SOURCES}
        ${CMAKE_SOURCE_DIR}/3rdparty/arc4random-src/arc4random_uniform.cpp
        #        ${CMAKE_SOURCE_DIR}/3rdparty/qqbonjour-src/BonjourServiceBrowser.cpp
        #        ${CMAKE_SOURCE_DIR}/3rdparty/qqbonjour-src/BonjourServiceResolver.cpp
        #        ${CMAKE_SOURCE_DIR}/3rdparty/qqbonjour-src/BonjourServiceRegister.cpp
        )

set(SHARED_HEADERS
        src/ACL.h
        src/Ban.h
        src/ByteSwap.h
        src/Channel.h
        src/Connection.h
        src/CryptographicHash.h
        src/CryptographicRandom.h
        src/CryptState.h
        src/FFDHE.h
        src/EnvUtils.h
        src/FFDHETable.h
        src/Group.h
        src/HostAddress.h
        src/HTMLFilter.h
        src/License.h
        src/licenses.h
        src/LogEmitter.h
        src/Message.h
        src/Net.h
        src/OSInfo.h
        src/PacketDataStream.h
        src/PasswordGenerator.h
        src/QAtomicIntCompat.h
        src/PlatformCheck.h
        src/qos2_mingw.h
        src/Qt4Compat.h
        src/SelfSignedCertificate.h
        src/ServerAddress.h
        src/ServerResolver.h
        src/ServerResolver_nosrv.h
        src/ServerResolverRecord.h
        src/SignalCurry.h
        src/SSLCipherInfo.h
        src/SSL.h
        src/SSLCipherInfoTable.h
        src/SSLLocks.h
        src/Timer.h
        src/User.h
        src/Version.h
        src/UnresolvedServerAddress.h
        ${PROTO_HEADERS}
        )

set(SHARED_SOURCES ${SHARED_SOURCE}
        #${SPEEX_SOURCES}
        )

set(SHARED_LIBS pcre16 celt0.0.7.0 celt0.0.11.0 ${Protobuf_LIBRARIES} ${RM_OPENSSL_LIBS} speex ${Boost_LIBRARIES} opus sndfile)
set(SHARED_INCLUDES ${CMAKE_SOURCE_DIR}/src/ ${CMAKE_SOURCE_DIR}/src/ ${CMAKE_BINARY_DIR}/3rdparty/openssl/crypto
        ${RM_OPENSSL_INCLUDE} ${CMAKE_BINARY_DIR}/3rdparty/libsndfile/src ${Protobuf_INCLUDE_DIR})
set(SHARED_DEFS -DUSE_NO_SRV -DUSE_OPUS -DPCRE_STATIC)

if(WIN32)
    set(SHARED_DEFS ${SHARED_DEFS} -DUNICODE -DRESTRICT=__restrict)
    set(SHARED_LIBS ${SHARED_LIBS} crypt32 ws2_32 qwave celt0.0.7.0 celt0.0.11.0 ksuser dbghelp)
else()
    set(SHARED_DEFS ${SHARED_DEFS} -DRESTRICT=__restrict__)
endif()

set(SHARED_LIBS Qt5::Core Qt5::Gui Qt5::Network Qt5::Widgets Qt5::DBus Qt5::Xml Qt5::Sql Qt5::Svg ${SHARED_LIBS})
#[[
add_library(RmShared STATIC ${SHARED_SOURCE} ${SPEEX_SOURCES})
target_link_libraries(RmShared PUBLIC Qt5::Gui Qt5::Network Qt5::Widgets Qt5::DBus Qt5::Xml Qt5::Sql ${Protobuf_LIBRARIES} crypto ssl)
target_include_directories(RmShared
        PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}/src/>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/ ${CMAKE_BINARY_DIR}/3rdparty/openssl/crypto ${CMAKE_BINARY_DIR}/3rdparty/openssl/ssl>
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src/
        )
target_compile_definitions(RmShared PRIVATE -DUSE_NO_SRV)
]]
