cmake_minimum_required(VERSION 3.7)
project(pr_mumble)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTOUIC ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin)
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/lib)
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

#link_directories(${CMAKE_BINARY_DIR}/lib)
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake/modules)

if (CMAKE_BUILD_TYPE MATCHES Debug)
        add_definitions(-DRM_DEBUG)
endif()

if (WIN32)
	add_definitions(-D_WIN32_WINNT=_WIN32_WINNT_WIN7)
endif()

#include_directories(cmake/general ${CMAKE_BINARY_DIR}/3rdparty ${CMAKE_BINARY_DIR}/3rdparty/openssl/ssl ${CMAKE_BINARY_DIR}/3rdparty/openssl/crypto)
include_directories(cmake/general ${CMAKE_BINARY_DIR}/3rdparty)

if (UNIX)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -msse4.1")
endif()

set(BUILD_OBJECT_LIBRARY_ONLY OFF CACHE BOOL "")

add_subdirectory(cmake/celt)
if (WIN32 AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
find_package(opus REQUIRED)
include_directories(${OPUS_INCLUDE_DIRS})
else()
add_subdirectory(cmake/opus)
endif()

if (WIN32 AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
else()
add_subdirectory(3rdparty/libsndfile)
endif()
include(cmake/speex/speex.cmake)

include(cmake/protobuf/protobuf.cmake)

find_package(GitInfo)
git_wc_info(${PROJECT_SOURCE_DIR} RM)

if ("${RM_WC_BRANCH}" EQUAL "production")
add_definitions(-DRM_PRODUCTION)
message("Building in RM production mode")
else()
add_definitions(-DRM_DEVELOPMENT)
message("Building in RM development mode")
endif()

message(STATUS "The current git branch is ${RM_WC_BRANCH}")

include(cmake/mumble/updater.cmake)
include(cmake/mumble/shared.cmake)
include(cmake/mumble/server.cmake)
include(cmake/mumble/client.cmake)

if (WIN32 AND NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") #only if win32 and not mxe
add_custom_target(Qt5CopyBinaries
        # todo: check if debug and release folder exist
        # debug version
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/libEGLd.dll          ${CMAKE_BINARY_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/libGLESv2d.dll       ${CMAKE_BINARY_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Cored.dll         ${CMAKE_BINARY_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Guid.dll          ${CMAKE_BINARY_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Networkd.dll      ${CMAKE_BINARY_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5OpenGLd.dll       ${CMAKE_BINARY_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Sqld.dll          ${CMAKE_BINARY_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Widgetsd.dll      ${CMAKE_BINARY_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Xmld.dll          ${CMAKE_BINARY_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5XmlPatternsd.dll  ${CMAKE_BINARY_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Svgd.dll          ${CMAKE_BINARY_DIR}/bin
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Dbusd.dll          ${CMAKE_BINARY_DIR}/bin
#[[
        # release version
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/libEGL.dll           ${CMAKE_BINARY_DIR}/
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/libGLESv2.dll        ${CMAKE_BINARY_DIR}/
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Core.dll          ${CMAKE_BINARY_DIR}/
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Gui.dll           ${CMAKE_BINARY_DIR}/
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Network.dll       ${CMAKE_BINARY_DIR}/
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5OpenGL.dll        ${CMAKE_BINARY_DIR}/
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Sql.dll           ${CMAKE_BINARY_DIR}/
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Widgets.dll       ${CMAKE_BINARY_DIR}/
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Xml.dll           ${CMAKE_BINARY_DIR}/
        COMMAND ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5XmlPatterns.dll   ${CMAKE_BINARY_DIR}/
]]
        # Output Message
        COMMENT "Copying Qt binaries from '${Qt5Core_DIR}/../../bin/' to '${CMAKE_BINARY_DIR}'" VERBATIM
        )

#add_dependencies(RmMurmur Qt5CopyBinaries)
add_dependencies(RmMumble Qt5CopyBinaries)
endif()
