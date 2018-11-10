cmake_minimum_required(VERSION 3.12)
project(pr_mumble)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(3rdparty/opus-cmake)
add_subdirectory(3rdparty/libsndfile)

include(cmake/protobuf/protobuf.cmake)
include(cmake/speex/speex.cmake)

include(cmake/mumble/shared.cmake)

include(cmake/mumble/server.cmake)
include(cmake/mumble/client.cmake)
