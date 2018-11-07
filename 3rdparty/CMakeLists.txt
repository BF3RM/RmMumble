add_definitions(-DHAVE_CONFIG_H)

SET(CELT_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/arch.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/bands.h
       # ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/c64_fft.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/celt.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/celt_header.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/celt_types.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/cwrs.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/ecintrin.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/entcode.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/entdec.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/entenc.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/fixed_c5x.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/fixed_c6x.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/fixed_debug.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/fixed_generic.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/float_cast.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/_kiss_fft_guts.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/kiss_fft.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/laplace.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/mathops.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/mdct.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/mfrngcod.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/modes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/os_support.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/pitch.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/plc.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/quant_bands.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/rate.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/stack_alloc.h
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/vq.h
        ${CMAKE_SOURCE_DIR}/cmake/celt/config.h
        PARENT_SCOPE
        )

SET(CELT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/bands.c
        #${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/c64_fft.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/celt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/cwrs.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/dump_modes.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/entcode.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/entdec.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/entenc.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/header.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/kiss_fft.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/laplace.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/mathops.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/mdct.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/modes.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/pitch.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/plc.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/quant_bands.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/rate.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/static_modes_fixed.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/static_modes_float.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/testcelt.c
        ${CMAKE_CURRENT_SOURCE_DIR}/celt-0.11.0-src/libcelt/vq.c
        PARENT_SCOPE)

#add_library(celt ${CELT_HEADERS} ${CELT_SRCS})
#target_include_directories(celt PRIVATE ${CMAKE_SOURCE_DIR}/cmake/celt/)
#set_property(TARGET celt PROPERTY C_STANDARD 99)

