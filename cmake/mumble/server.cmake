set(MURMUR_SOURCES
        #src/murmur/BonjourServer.cpp
        #src/murmur/BonjourServer.h
        #        src/murmur/DBus.cpp
        #        src/murmur/DBus.h
        src/murmur/Cert.cpp
        src/murmur/main.cpp
        src/murmur/Messages.cpp
        src/murmur/Meta.cpp
        src/murmur/PBKDF2.cpp
        src/murmur/Register.cpp
        src/murmur/RPC.cpp
        src/murmur/Server.cpp
        src/murmur/ServerDB.cpp
        src/murmur/ServerUser.cpp
        src/ServerResolver_qt5.cpp

        #        src/murmur/MurmurGRPCImpl.cpp
        #        src/murmur/MurmurGRPCImpl.h
        #        src/murmur/MurmurIce.cpp
        #        src/murmur/MurmurIce.h
        #        src/murmur/MurmurIceWrapper.cpp
        #        src/murmur_grpcwrapper_protoc_plugin/main.cpp
        )

set(MURMUR_HEADERS
        src/murmur/PBKDF2.h
        src/murmur/Server.h
        src/murmur/ServerDB.h
#        src/murmur/UnixMurmur.h
        src/murmur/Meta.h
        src/murmur/murmur_pch.h
        src/murmur/MurmurI.h
        )

if(WIN32)
    list(APPEND MURMUR_SOURCES src/murmur/About.cpp src/murmur/About.h src/murmur/Tray.cpp)
    list(APPEND MURMUR_HEADERS src/murmur/Tray.h)
else()
    list(APPEND MURMUR_SOURCES src/murmur/UnixMurmur.cpp)
    list(APPEND MURMUR_HEADERS src/murmur/UnixMurmur.h)
endif()

set(ADDITIONAL_LIBS "")
if(UNIX)
    list(APPEND ADDITIONAL_LIBS cap)
endif()

qt5_wrap_cpp(QT5_SRC src/ServerResolver.h)

add_executable(RmMurmur ${MURMUR_SOURCES} ${MURMUR_HEADERS} ${SHARED_SOURCES} ${QT5_SRC} ${SHARED_OBJS})
set_target_properties(RmMurmur PROPERTIES ENABLE_EXPORTS 1)
target_link_libraries(RmMurmur PRIVATE ${SHARED_LIBS} ${ADDITIONAL_LIBS} speex)
target_include_directories(RmMurmur
        PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}/src/murmur
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/murmur>
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src/murmur ${SHARED_INCLUDES}
        )
target_compile_definitions(RmMurmur PRIVATE -DMURMUR -DUSE_NO_SRV ${SHARED_DEFS})


#[[
add_executable(RmMurmur ${MURMUR_SOURCES} ${MURMUR_HEADERS})
target_link_libraries(RmMurmur PRIVATE RmShared ${ADDITIONAL_LIBS} speex)
target_include_directories(RmMurmur
        PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}/src/murmur
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/murmur>
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src/murmur
        )
target_compile_definitions(RmMurmur PRIVATE -DMURMUR -DUSE_NO_SRV)
target_compile_definitions(RmShared PRIVATE -DMURMUR)

]]
