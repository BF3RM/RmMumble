find_package(Qt5 COMPONENTS Network)

add_library(UpdaterLib STATIC ${CMAKE_SOURCE_DIR}/src/updater/RmUpdater.cpp)
target_include_directories(UpdaterLib PUBLIC ${CMAKE_SOURCE_DIR}/src/updater)
target_link_libraries(UpdaterLib PRIVATE Qt5::Network)