find_package(Qt5 COMPONENTS Network Core Widgets)
file(GLOB MINIZIP_SOURCES ${CMAKE_SOURCE_DIR}/3rdparty/zlib/contrib/minizip/*.c)

if(UNIX)
    list(REMOVE_ITEM MINIZIP_SOURCES "${CMAKE_SOURCE_DIR}/3rdparty/zlib/contrib/minizip/iowin32.c")
endif()

add_library(UpdaterLib STATIC ${CMAKE_SOURCE_DIR}/src/updater/RmUpdater.cpp ${MINIZIP_SOURCES})
target_include_directories(UpdaterLib PUBLIC ${CMAKE_SOURCE_DIR}/src/updater ${CMAKE_SOURCE_DIR}/3rdparty/zlib/ ${CMAKE_BINARY_DIR}/3rdparty/zlib)
target_link_libraries(UpdaterLib PRIVATE Qt5::Network Qt5::Widgets zlib iphlpapi ssl crypto crypt32 ws2_32)

qt5_wrap_cpp(MOCS src/updater/Progress.h)

add_executable(RmUpdater ${MOCS} ${CMAKE_SOURCE_DIR}/src/updater/main.cpp ${CMAKE_SOURCE_DIR}/src/updater/Progress.cpp)
target_link_libraries(RmUpdater PRIVATE UpdaterLib Qt5::Core Qt5::Widgets)
