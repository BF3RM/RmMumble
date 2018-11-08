file(GLOB SPEEX_SOURCES_C ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/*.c)
file(GLOB SPEEX_SOURCES_H ${CMAKE_SOURCE_DIR}/3rdparty/speex-src/src/*.h)

set(SPEEX_SOURCES ${SPEEX_SOURCES_C} ${SPEEX_SOURCES_H})
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/speex-src/include)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/speexdsp-src/include)