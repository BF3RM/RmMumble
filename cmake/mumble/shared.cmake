find_package(Qt5 REQUIRED Gui Network Widgets DBus Xml Sql)
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

include(cmake/celt/celt.cmake)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

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
        src/SSL.cpp
        src/SSLCipherInfo.cpp
        src/SSLLocks.cpp
        src/Timer.cpp
        src/UnresolvedServerAddress.cpp
        src/User.cpp
        src/Version.cpp
#        ${CELT_SOURCES}
        ${PROTO_SRCS}
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
        ${PROTO_HDRS}
        )

add_library(RmShared ${SHARED_SOURCE} ${SHARED_HEADERS})
target_link_libraries(RmShared PRIVATE Qt5::Gui Qt5::Network Qt5::Widgets Qt5::DBus Qt5::Xml Qt5::Sql ${OPENSSL_LIBRARIES} ${Protobuf_LIBRARIES})
target_include_directories(RmShared
        PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}/src/>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/>
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src/
        )