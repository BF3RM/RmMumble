project(celt C)

set(CELT_C
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/celt.c
${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt/bands.c
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

add_library(celt0.0.7.0 SHARED ${CELT_C})
target_link_libraries(celt0.0.7.0 PRIVATE -Wl,--allow-multiple-definition)
if(WIN32)
target_compile_definitions(celt0.0.7.0 PRIVATE -DHAVE_CONFIG_H WIN32 _WIN32)
set(CONFIG_INCLUDE ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-build/win32)
else()
target_compile_definitions(celt0.0.7.0 PRIVATE -DHAVE_CONFIG_H)
set(CONFIG_INCLUDE ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-build/)
endif()

target_include_directories(celt0.0.7.0 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt>
    $<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}/3rdparty/celt-0.7.0-src/libcelt>
    PRIVATE ${CONFIG_INCLUDE})


set (celt0.11.0_SOURCES 
 ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt/bands.c 
 ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt/celt.c 
 ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt/cwrs.c 
 ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt/entcode.c 
 ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt/entdec.c 
 ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt/entenc.c 
 ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt/header.c 
 ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt/kiss_fft.c
 ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt/laplace.c 
 ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt/mathops.c 
 ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt/mdct.c 
 ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt/modes.c 
 ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt/pitch.c 
 ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt/plc.c 
 ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt/quant_bands.c 
 ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt/rate.c 
 ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt/vq.c 
 )

add_library(celt0.0.11.0 SHARED ${celt0.11.0_SOURCES})
target_link_libraries(celt0.0.11.0 PRIVATE -Wl,--allow-multiple-definition)
if(WIN32)
 target_compile_definitions(celt0.0.11.0 PRIVATE -DHAVE_CONFIG_H WIN32 _WIN32)
 set(CONFIG_INCLUDE ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-build/win32)
else()
 target_compile_definitions(celt0.0.11.0 PRIVATE -DHAVE_CONFIG_H)
 set(CONFIG_INCLUDE ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-build/)
endif()
target_compile_definitions(celt0.0.11.0 PRIVATE -DHAVE_CONFIG_H WIN32 _WIN32)
target_include_directories(celt0.0.11.0 PUBLIC
$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt>
$<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt>
PRIVATE ${CONFIG_INCLUDE})
