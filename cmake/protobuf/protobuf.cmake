include(ExternalProject)

find_package(protobuf REQUIRED)

protobuf_generate_cpp(PROTO_SOURCES PROTO_HEADERS ${CMAKE_SOURCE_DIR}/src/Mumble.proto)