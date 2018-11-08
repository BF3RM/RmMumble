find_package(Protobuf REQUIRED)
protobuf_generate_cpp(PROTO_SRCS_TMP PROTO_HDRS_TMP ${CMAKE_SOURCE_DIR}/src/Mumble.proto)

set(PROTO_SRCS ${PROTO_SRCS_TMP})
set(PROTO_HDRS ${PROTO_HDRS_TMP})