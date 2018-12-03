project(celt C)

set(CELT_C
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/bands.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/celt.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/cwrs.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/cwrs.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/entcode.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/entdec.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/entenc.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/header.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/kiss_fft.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/kiss_fftr.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/laplace.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/mdct.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/modes.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/psy.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/pitch.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/quant_bands.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/rangedec.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/rangeenc.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/rate.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/vq.c
)


add_library(celt STATIC ${CELT_C})
target_include_directories(celt PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt>
    $<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt>
    PRIVATE ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-build/win32)
target_compile_definitions(celt PRIVATE -DHAVE_CONFIG_H WIN32 _WIN32)
