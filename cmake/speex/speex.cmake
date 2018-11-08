file(GLOB SPEEX_SOURCES_C ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/*.c)
file(GLOB SPEEX_SOURCES_H ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/*.h)

set(SPEEX_SOURCES_C ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/getopt.c
        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/getopt1.c
        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/skeleton.c
#        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/speexdec.c
#        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/speexenc.c
        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/wav_io.c
        ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/wave_out.c
        )

set(SPEEX_SOURCES ${SPEEX_SOURCES_C})
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/speex-src/include)
#include_directories(${CMAKE_SOURCE_DIR}/3rdparty/speexdsp-src/include)
include_directories(${CMAKE_SOURCE_DIR}/cmake/speex)

add_library(speex ${SPEEX_SOURCES_C})