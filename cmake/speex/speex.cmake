add_subdirectory(3rdparty/ogg)

file(GLOB SPEEX_SOURCES_C ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/libspeex/*.c)
file(GLOB SPEEX_SOURCES_C_REMOVE ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/libspeex/test*.c)
list(REMOVE_ITEM SPEEX_SOURCES_C ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/libspeex/smallft.c)
list(REMOVE_ITEM SPEEX_SOURCES_C ${SPEEX_SOURCES_C_REMOVE})


set(SPEEX_SOURCES_C
        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/getopt.c
        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/getopt1.c
        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/skeleton.c
#        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/speexdec.c
#        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/speexenc.c
        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/wav_io.c
        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/wave_out.c
#        ${CMAKE_SOURCE_DIR}/3rdparty/smallft-src/smallft.cpp
        ${SPEEX_SOURCES_C}
        )

file(GLOB SPEEXDSP_SOURCES ${CMAKE_SOURCE_DIR}/3rdparty/speexdsp-src/libspeexdsp/*.c)
file(GLOB SPEEXDSP_SOURCES_REMOVE ${CMAKE_SOURCE_DIR}/3rdparty/speexdsp-src/libspeexdsp/test*.c)
list(REMOVE_ITEM SPEEXDSP_SOURCES ${SPEEXDSP_SOURCES_REMOVE})

set(SPEEX_SOURCES ${SPEEX_SOURCES_C} ${SPEEXDSP_SOURCES})
#include_directories(${CMAKE_SOURCE_DIR}/3rdparty/speexdsp-src/include)
if(WIN32)
    set(SPEEX_SOURCES ${SPEEX_SOURCES} 3rdparty/speex-build/mumble_speex_init.c)
endif()

add_library(speex ${SPEEX_SOURCES})

target_include_directories(speex PUBLIC ${CMAKE_SOURCE_DIR}/cmake/speex ${CMAKE_SOURCE_DIR}/3rdparty/smallft-src/ ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/include ${CMAKE_SOURCE_DIR}/3rdparty/speexdsp-src/include)
target_compile_definitions(speex PRIVATE -DHAVE_CONFIG_H -DUSE_SMALLFT)
if(WIN32)
    target_include_directories(speex PRIVATE 3rdparty/speex-build/win32 3rdparty/ogg/include)
    #target_link_libraries(speex PRIVATE ogg crypto ssl)
    target_compile_definitions(speex PRIVATE -DWIN32 -D_WINDOWS -D_USE_MATH_DEFINES)
    target_include_directories(speex PRIVATE ${CMAKE_BINARY_DIR}/3rdparty/openssl/crypto ${CMAKE_BINARY_DIR}/3rdparty/openssl/ssl ${CMAKE_SOURCE_DIR}/3rdparty/speex-build/win32)
elseif(UNIX)
    target_include_directories(speex PRIVATE 3rdparty/speex-build/)
endif()
