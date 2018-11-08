cmake_minimum_required(VERSION 3.12)
project(pr_mumble)

set(CMAKE_CXX_STANDARD 14)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

include(cmake/protobuf/protobuf.cmake)

include(cmake/mumble/shared.cmake)
include(cmake/mumble/client.cmake)
include(cmake/mumble/server.cmake)

#[[

include_directories(plugins)
include_directories(src)
include_directories(src/mumble)
include_directories(src/mumble/widgets)
#include_directories(src/mumble_proto)
include_directories(src/murmur)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/arc4random-src/)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/qqbonjour-src/)


set(MUMBLE_SOURCE
        src/mumble/release/qrc_mumble.cpp
        src/mumble/release/qrc_mumble_flags_0.cpp
        src/mumble/release/qrc_mumble_translations.cpp
        src/mumble/release/qrc_MumbleTheme.cpp
        src/mumble/widgets/MUComboBox.cpp
        src/mumble/widgets/MUComboBox.h
        src/mumble/About.cpp
        src/mumble/About.h
        src/mumble/ACLEditor.cpp
        src/mumble/ACLEditor.h
        src/mumble/ALSAAudio.cpp
        src/mumble/ALSAAudio.h
        src/mumble/ApplicationPalette.h
        src/mumble/ApplicationPaletteTemplate.h
        src/mumble/AppNap.h
        src/mumble/AppNap.mm
        src/mumble/ASIOInput.cpp
        src/mumble/ASIOInput.h
        src/mumble/Audio.cpp
        src/mumble/Audio.h
        src/mumble/AudioConfigDialog.cpp
        src/mumble/AudioConfigDialog.h
        src/mumble/AudioInput.cpp
        src/mumble/AudioInput.h
        src/mumble/AudioOutput.cpp
        src/mumble/AudioOutput.h
        src/mumble/AudioOutputSample.cpp
        src/mumble/AudioOutputSample.h
        src/mumble/AudioOutputSpeech.cpp
        src/mumble/AudioOutputSpeech.h
        src/mumble/AudioOutputUser.cpp
        src/mumble/AudioOutputUser.h
        src/mumble/AudioStats.cpp
        src/mumble/AudioStats.h
        src/mumble/AudioWizard.cpp
        src/mumble/AudioWizard.h
        src/mumble/BanEditor.cpp
        src/mumble/BanEditor.h
        src/mumble/BonjourClient.cpp
        src/mumble/BonjourClient.h
        src/mumble/CELTCodec.cpp
        src/mumble/CELTCodec.h
        src/mumble/CELTCodec_sbcelt.cpp
        src/mumble/Cert.cpp
        src/mumble/Cert.h
        src/mumble/ClientUser.cpp
        src/mumble/ClientUser.h
        src/mumble/ConfigDialog.cpp
        src/mumble/ConfigDialog.h
        src/mumble/ConfigWidget.cpp
        src/mumble/ConfigWidget.h
        src/mumble/ConnectDialog.cpp
        src/mumble/ConnectDialog.h
        src/mumble/CoreAudio.cpp
        src/mumble/CoreAudio.h
        src/mumble/CrashReporter.cpp
        src/mumble/CrashReporter.h
        src/mumble/CustomElements.cpp
        src/mumble/CustomElements.h
        src/mumble/Database.cpp
        src/mumble/Database.h
        src/mumble/DBus.cpp
        src/mumble/DBus.h
        src/mumble/DeveloperConsole.cpp
        src/mumble/DeveloperConsole.h
        src/mumble/DirectSound.cpp
        src/mumble/DirectSound.h
        src/mumble/G15LCDEngine_helper.cpp
        src/mumble/G15LCDEngine_helper.h
        src/mumble/G15LCDEngine_lglcd.cpp
        src/mumble/G15LCDEngine_lglcd.h
        src/mumble/G15LCDEngine_unix.cpp
        src/mumble/G15LCDEngine_unix.h
        src/mumble/GKey.cpp
        src/mumble/GKey.h
        src/mumble/Global.cpp
        src/mumble/Global.h
        src/mumble/GlobalShortcut.cpp
        src/mumble/GlobalShortcut.h
        src/mumble/GlobalShortcut_macx.h
        src/mumble/GlobalShortcut_macx.mm
        src/mumble/GlobalShortcut_unix.cpp
        src/mumble/GlobalShortcut_unix.h
        src/mumble/GlobalShortcut_win.cpp
        src/mumble/GlobalShortcut_win.h
        src/mumble/JackAudio.cpp
        src/mumble/JackAudio.h
        src/mumble/LCD.cpp
        src/mumble/LCD.h
        src/mumble/Log.cpp
        src/mumble/Log.h
        src/mumble/Log_macx.mm
        src/mumble/Log_unix.cpp
        src/mumble/Log_win.cpp
        src/mumble/LookConfig.cpp
        src/mumble/LookConfig.h
        src/mumble/main.cpp
        src/mumble/MainWindow.cpp
        src/mumble/MainWindow.h
        src/mumble/ManualPlugin.cpp
        src/mumble/ManualPlugin.h
        src/mumble/Messages.cpp
        src/mumble/mumble_pch.hpp
        src/mumble/mumble_pch.hpp.cpp
        src/mumble/MumbleApplication.cpp
        src/mumble/MumbleApplication.h
        src/mumble/murmur_pch.h
        src/mumble/NetworkConfig.cpp
        src/mumble/NetworkConfig.h
        src/mumble/OpusCodec.cpp
        src/mumble/OpusCodec.h
        src/mumble/os_early_win.cpp
        src/mumble/os_macx.mm
        src/mumble/os_unix.cpp
        src/mumble/os_win.cpp
        src/mumble/OSS.cpp
        src/mumble/OSS.h
        src/mumble/Overlay.cpp
        src/mumble/Overlay.h
        src/mumble/Overlay_macx.mm
        src/mumble/Overlay_unix.cpp
        src/mumble/Overlay_win.cpp
        src/mumble/Overlay_win.h
        src/mumble/OverlayClient.cpp
        src/mumble/OverlayClient.h
        src/mumble/OverlayConfig.cpp
        src/mumble/OverlayConfig.h
        src/mumble/OverlayEditor.cpp
        src/mumble/OverlayEditor.h
        src/mumble/OverlayEditorScene.cpp
        src/mumble/OverlayEditorScene.h
        src/mumble/OverlayPositionableItem.cpp
        src/mumble/OverlayPositionableItem.h
        src/mumble/OverlayText.cpp
        src/mumble/OverlayText.h
        src/mumble/OverlayUser.cpp
        src/mumble/OverlayUser.h
        src/mumble/OverlayUserGroup.cpp
        src/mumble/OverlayUserGroup.h
        src/mumble/PAAudio.cpp
        src/mumble/PAAudio.h
        src/mumble/PathListWidget.cpp
        src/mumble/PathListWidget.h
        src/mumble/Plugins.cpp
        src/mumble/Plugins.h
        src/mumble/PTTButtonWidget.cpp
        src/mumble/PTTButtonWidget.h
        src/mumble/PulseAudio.cpp
        src/mumble/PulseAudio.h
        src/mumble/RichTextEditor.cpp
        src/mumble/RichTextEditor.h
        src/mumble/RMMessage.h
        src/mumble/RMSocket.cpp
        src/mumble/RMSocket.h
        src/mumble/ServerHandler.cpp
        src/mumble/ServerHandler.h
        src/mumble/Settings.cpp
        src/mumble/Settings.h
        src/mumble/SharedMemory.cpp
        src/mumble/SharedMemory.h
        src/mumble/SharedMemory_unix.cpp
        src/mumble/SharedMemory_win.cpp
        src/mumble/SocketRPC.cpp
        src/mumble/SocketRPC.h
        src/mumble/SvgIcon.cpp
        src/mumble/SvgIcon.h
        src/mumble/TaskList.cpp
        src/mumble/TaskList.h
        src/mumble/TextMessage.cpp
        src/mumble/TextMessage.h
        src/mumble/TextToSpeech.cpp
        src/mumble/TextToSpeech.h
        src/mumble/TextToSpeech_macx.mm
        src/mumble/TextToSpeech_unix.cpp
        src/mumble/TextToSpeech_win.cpp
        src/mumble/ThemeInfo.cpp
        src/mumble/ThemeInfo.h
        src/mumble/Themes.cpp
        src/mumble/Themes.h
        src/mumble/Tokens.cpp
        src/mumble/Tokens.h
        src/mumble/Usage.cpp
        src/mumble/Usage.h
        src/mumble/UserEdit.cpp
        src/mumble/UserEdit.h
        src/mumble/UserInformation.cpp
        src/mumble/UserInformation.h
        src/mumble/UserListModel.cpp
        src/mumble/UserListModel.h
        src/mumble/UserLocalVolumeDialog.cpp
        src/mumble/UserLocalVolumeDialog.h
        src/mumble/UserLockFile.h
        src/mumble/UserLockFile_win.cpp
        src/mumble/UserModel.cpp
        src/mumble/UserModel.h
        src/mumble/UserView.cpp
        src/mumble/UserView.h
        src/mumble/VersionCheck.cpp
        src/mumble/VersionCheck.h
        src/mumble/ViewCert.cpp
        src/mumble/ViewCert.h
        src/mumble/VoiceRecorder.cpp
        src/mumble/VoiceRecorder.h
        src/mumble/VoiceRecorderDialog.cpp
        src/mumble/VoiceRecorderDialog.h
        src/mumble/WASAPI.cpp
        src/mumble/WASAPI.h
        src/mumble/WASAPINotificationClient.cpp
        src/mumble/WASAPINotificationClient.h
        src/mumble/WebFetch.cpp
        src/mumble/WebFetch.h
        src/mumble/WinGUIDs.cpp
        src/mumble/XboxInput.cpp
        src/mumble/XboxInput.h
        src/mumble/XMLTools.cpp
        src/mumble/XMLTools.h
        src/mumble_exe/mumble_exe.cpp
        src/mumble_exe/Overlay.cpp
        )

set(TESTS_SOURCES
        src/tests/TestCrypt/TestCrypt.cpp
        src/tests/TestCryptographicHash/TestCryptographicHash.cpp
        src/tests/TestCryptographicRandom/TestCryptographicRandom.cpp
        src/tests/TestFFDHE/TestFFDHE.cpp
        src/tests/TestPacketDataStream/TestPacketDataStream.cpp
        src/tests/TestPasswordGenerator/TestPasswordGenerator.cpp
        src/tests/TestSelfSignedCertificate/TestSelfSignedCertificate.cpp
        src/tests/TestServerAddress/TestServerAddress.cpp
        src/tests/TestServerResolver/TestServerResolver.cpp
        src/tests/TestSSLLocks/TestSSLLocks.cpp
        src/tests/TestStdAbs/TestStdAbs.cpp
        src/tests/TestTimer/TestTimer.cpp
        src/tests/TestUnresolvedServerAddress/TestUnresolvedServerAddress.cpp
        src/tests/TestXMLTools/TestXMLTools.cpp
        src/tests/Benchmark.cpp
        src/tests/Collections.cpp
        src/tests/Emit.cpp
        src/tests/Hash.cpp
        src/tests/Lock.cpp
        src/tests/OverlayTest.cpp
        src/tests/ProtoBuf.cpp
        src/tests/Resample.cpp
        src/tests/TestLink.cpp)

#add_executable(pr_mumble
#        plugins/link/link-posix.cpp
#        plugins/link/link.cpp
#        plugins/rl/rl.cpp
#        plugins/rm/rm.cpp
#        plugins/mumble_plugin.h
#        plugins/mumble_plugin_linux.h
#        plugins/mumble_plugin_utils.h
#        plugins/mumble_plugin_win32.h
#        plugins/null_plugin.cpp
#
#
#    )

set(MURMUR_ADDITIONAL_LIBS "")

if(UNIX)
list(APPEND MURMUR_ADDITIONAL_LIBS cap)
endif()

find_package(Qt5 REQUIRED Gui Network Widgets DBus Xml Sql)
find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(RealityMurmur ${SHARED_SOURCE} ${MURMUR_SOURCE})
target_include_directories(RealityMurmur PRIVATE ${CMAKE_SOURCE_DIR}/3rdparty/celt-0.11.0-src/libcelt)
target_link_libraries(RealityMurmur Qt5::Gui Qt5::Network Qt5::Widgets Qt5::DBus Qt5::Xml Qt5::Sql ${OPENSSL_LIBRARIES} ${Protobuf_LIBRARIES} ${MURMUR_ADDITIONAL_LIBS})
target_compile_definitions(RealityMurmur PRIVATE MURMUR=1)

]]