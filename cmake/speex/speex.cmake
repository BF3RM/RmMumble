file(GLOB SPEEX_SOURCES_C ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/libspeex/*.c)

set(SPEEX_SOURCES_C ${SPEEX_SOURCES_C} ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/getopt.c
        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/getopt1.c
        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/skeleton.c
#        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/speexdec.c
#        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/speexenc.c
        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/wav_io.c
        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/wave_out.c
        )

file(GLOB SPEEXDSP_SOURCES ${CMAKE_SOURCE_DIR}/3rdparty/speexdsp-src/libspeexdsp/*.c)

set(SPEEX_SOURCES ${SPEEX_SOURCES_C} ${SPEEXDSP_SOURCES})
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/speex-src/include ${CMAKE_SOURCE_DIR}/3rdparty/speexdsp-src/include)
#include_directories(${CMAKE_SOURCE_DIR}/3rdparty/speexdsp-src/include)
include_directories(${CMAKE_SOURCE_DIR}/cmake/speex)

add_library(speex ${SPEEX_SOURCES})
target_compile_definitions(speex PRIVATE -DHAVE_CONFIG_H)
if(WIN32)
    target_include_directories(speex PRIVATE 3rdparty/speex-build/win32)
elseif(UNIX)
    target_include_directories(speex PRIVATE 3rdparty/speex-build/)
endif()