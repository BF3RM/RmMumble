find_package(Qt5 COMPONENTS Svg REQUIRED)

set(MumbleExeName RmMumbleApp)

set(MUMBLE_SOURCES
#        src/mumble/release/qrc_mumble.cpp
#        src/mumble/release/qrc_mumble_flags_0.cpp
#        src/mumble/release/qrc_mumble_translations.cpp
#        src/mumble/release/qrc_MumbleTheme.cpp
        src/mumble/widgets/MUComboBox.cpp
        src/mumble/widgets/MUComboBox.h
        src/mumble/Rm3DSocket.cpp
        src/mumble/About.cpp
        src/mumble/About.h
        src/mumble/ACLEditor.cpp
        src/mumble/ACLEditor.h
        src/mumble/ApplicationPalette.h
#        src/mumble/ApplicationPaletteTemplate.h
        src/mumble/AppNap.h
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
        #src/mumble/BonjourClient.cpp
        #src/mumble/BonjourClient.h
        src/mumble/CELTCodec.cpp
        src/mumble/CELTCodec.h
#        src/mumble/CELTCodec_sbcelt.cpp
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
#        src/mumble/G15LCDEngine_helper.cpp
#        src/mumble/G15LCDEngine_helper.h
#        src/mumble/G15LCDEngine_lglcd.cpp
#        src/mumble/G15LCDEngine_lglcd.h
#        src/mumble/GKey.cpp
#        src/mumble/GKey.h
        src/mumble/Global.cpp
        src/mumble/Global.h
        src/mumble/GlobalShortcut.cpp
        src/mumble/GlobalShortcut.h
#        src/mumble/JackAudio.cpp
#        src/mumble/JackAudio.h
        src/mumble/LCD.cpp
        src/mumble/LCD.h
        src/mumble/Log.cpp
        src/mumble/Log.h

        src/mumble/LookConfig.cpp
        src/mumble/LookConfig.h
        src/mumble/MainWindow.cpp
        src/mumble/MainWindow.h
        src/mumble/Messages.cpp
        src/mumble/main.cpp
        src/mumble/mumble_pch.hpp
        src/mumble/mumble_pch.hpp.cpp
        src/mumble/ManualPlugin.cpp
        src/mumble/ManualPlugin.h
        src/mumble/MumbleApplication.cpp
        src/mumble/MumbleApplication.h
        src/mumble/NetworkConfig.cpp
        src/mumble/NetworkConfig.h
        src/mumble/OpusCodec.cpp
        src/mumble/OpusCodec.h

        src/mumble/Overlay.cpp
        src/mumble/Overlay.h

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
#        src/mumble/PAAudio.cpp
#        src/mumble/PAAudio.h
        src/mumble/PathListWidget.cpp
        src/mumble/PathListWidget.h
        src/mumble/Plugins.cpp
        src/mumble/Plugins.h
        src/mumble/PTTButtonWidget.cpp
        src/mumble/PTTButtonWidget.h
        src/mumble/RichTextEditor.cpp
        src/mumble/RichTextEditor.h
        src/mumble/RMMessage.cpp
        src/mumble/RMMessage.h
        src/mumble/RMSocket.cpp
        src/mumble/RMSocket.h
        src/mumble/ServerHandler.cpp
        src/mumble/ServerHandler.h
        src/mumble/Settings.cpp
        src/mumble/Settings.h
        src/mumble/SharedMemory.cpp
        src/mumble/SharedMemory.h

        src/mumble/SocketRPC.cpp
        src/mumble/SocketRPC.h
        src/mumble/SvgIcon.cpp
        src/mumble/SvgIcon.h
        src/mumble/TextMessage.cpp
        src/mumble/TextMessage.h
#        src/mumble/TextToSpeech.h

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
        src/mumble/WebFetch.cpp
        src/mumble/WebFetch.h

        src/mumble/XMLTools.cpp
        src/mumble/XMLTools.h

        3rdparty/smallft-src/smallft.cpp
        3rdparty/smallft-src/smallft.h
        )

#set(MUMBLE_EXE_SOURCES src/mumble_exe/mumble_exe.cpp src/mumble_exe/Overlay.cpp)

if(WIN32)
    list(APPEND MUMBLE_SOURCES
            3rdparty/xinputcheck-src/xinputcheck.cpp
            src/mumble/UserLockFile_win.cpp
            #src/mumble/TextToSpeech_win.cpp
            src/mumble/SharedMemory_win.cpp
            src/mumble/Overlay_win.cpp
            src/mumble/Overlay_win.h
            src/mumble/os_early_win.cpp
            src/mumble/Log_win.cpp
            src/mumble/GlobalShortcut_win.cpp
            src/mumble/GlobalShortcut_win.h
            src/mumble/os_win.cpp
            src/mumble/WinGUIDs.cpp
            src/mumble/DirectSound.cpp
            src/mumble/DirectSound.h
            src/mumble/TaskList.cpp
            src/mumble/TaskList.h
            src/mumble/WASAPI.cpp
            src/mumble/WASAPI.h
            src/mumble/WASAPINotificationClient.cpp
            src/mumble/WASAPINotificationClient.h
            src/mumble/XboxInput.cpp
            src/mumble/XboxInput.h
            )
else()
    list(APPEND MUMBLE_SOURCES
            src/mumble/ALSAAudio.cpp
            src/mumble/ALSAAudio.h
            #src/mumble/TextToSpeech_unix.cpp
            src/mumble/SharedMemory_unix.cpp
            src/mumble/os_unix.cpp
            src/mumble/Overlay_unix.cpp
#            src/mumble/G15LCDEngine_unix.cpp
#            src/mumble/G15LCDEngine_unix.h
            src/mumble/GlobalShortcut_unix.cpp
            src/mumble/GlobalShortcut_unix.h
            src/mumble/Log_unix.cpp
            src/mumble/PulseAudio.cpp
            src/mumble/PulseAudio.h
            src/mumble/OSS.cpp
            src/mumble/OSS.h
            )
endif()

qt5_wrap_cpp(QT5_SRC src/ServerResolver.h src/SignalCurry.h)# src/mumble/TextToSpeech.h)
qt5_add_resources(MUMBLE_RESOURCES 
    ${CMAKE_SOURCE_DIR}/src/mumble/mumble.qrc 
#    ${CMAKE_SOURCE_DIR}/src/mumble/mumble_translations.qrc
    ${CMAKE_SOURCE_DIR}/themes/MumbleTheme.qrc
    ${CMAKE_SOURCE_DIR}/src/mumble/flags/mumble_flags_0.qrc)
set(ADDITIONAL_LIBS "")
set(FLAGS "")
if(UNIX)
    list(APPEND ADDITIONAL_LIBS cap X11 rt asound pulse)
elseif(WIN32)
    list(APPEND ADDITIONAL_LIBS user32 shlwapi avrt dsound wintrust delayimp dinput8 uuid dxguid)
    list(APPEND FLAGS WIN32)
endif()

set(DEFINITIONS "")

if(UNIX)
    set(MumbleExeName RmMumble)
    add_executable(${MumbleExeName} ${FLAGS} ${MUMBLE_SOURCES} ${SHARED_SOURCES} ${QT5_SRC} ${MUMBLE_RESOURCES})
else()
    add_library(${MumbleExeName} SHARED ${MUMBLE_SOURCES} ${SHARED_SOURCES} ${SHARED_OBJS} ${QT5_SRC} ${MUMBLE_RESOURCES})
    set_target_properties(${MumbleExeName} PROPERTIES PREFIX "")
    #add_executable(RmMumble ${FLAGS} ${MUMBLE_EXE_SOURCES})
    target_link_libraries(${MumbleExeName} PRIVATE shlwapi)
    target_compile_definitions(${MumbleExeName} PUBLIC -DUNICODE -DUSE_DBUS)
    add_executable(RmMumble ${FLAGS} src/mumble_exe/mumble_exe.cpp)
    target_link_libraries(RmMumble PRIVATE ${MumbleExeName} shlwapi)
endif()

set_target_properties(${MumbleExeName} 
    PROPERTIES 
    ENABLE_EXPORTS 1
    C_STANDARD 11)

target_link_libraries(${MumbleExeName} PRIVATE ${SHARED_LIBS} ${ADDITIONAL_LIBS} opus Qt5::Svg sndfile)
target_include_directories(${MumbleExeName}
        PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}/src/mumble
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/mumble ${CMAKE_SOURCE_DIR}/src/mumble/widgets ${CMAKE_SOURCE_DIR}/3rdparty/qqbonjour-src>
        PRIVATE
        #${CMAKE_SOURCE_DIR}/src/mumble ${OPENSSL_INCLUDE_DIR} 3rdparty/smallft-src ${SHARED_INCLUDES} 3rdparty/xinputcheck-src/ 3rdparty/asio/common 3rdparty/asio/host 3rdparty/asio/host/pc
        ${CMAKE_SOURCE_DIR}/src/mumble 3rdparty/smallft-src ${SHARED_INCLUDES} 3rdparty/xinputcheck-src/ 3rdparty/asio/common 3rdparty/asio/host 3rdparty/asio/host/pc
        )

target_compile_definitions(${MumbleExeName} PRIVATE -DUSE_NO_TTS -DMUMBLE -DNO_XINPUT2 ${SHARED_DEFS} ${DEFINITIONS} -DUSE_DBUS -DUSE_MANUAL_PLUGIN -DUSE_ASIO)

if(WIN32)
        set_target_properties(${MumbleExeName} PROPERTIES LINK_FLAGS_RELEASE "-delayload:shell32.dll")
        set_target_properties(${MumbleExeName} PROPERTIES LINK_FLAGS_DEBUG "-delayload:shell32.dll")
endif()

if(WIN32)
	add_library(RmRadio SHARED plugins/rm/rm.cpp)
	target_link_libraries(RmRadio PRIVATE psapi ws2_32)
	target_compile_definitions(RmRadio PRIVATE -DUNICODE -DRESTRICT=__restrict)
	target_compile_definitions(RmRadio PRIVATE -DRM_POSITIONAL_DEBUG)

    if (NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        add_library(PositionalAudioDebug SHARED plugins/positional-audio-debug/positional-audio-debug.cpp)
        target_include_directories(PositionalAudioDebug PRIVATE ${CMAKE_SOURCE_DIR}/plugins/positional-audio-debug/websocketpp ${CMAKE_SOURCE_DIR}/plugins/positional-audio-debug/asio/asio/include)
        target_link_libraries(PositionalAudioDebug PRIVATE psapi ws2_32)
        target_compile_definitions(PositionalAudioDebug PRIVATE -DRESTRICT=__restrict)
        set(DEFINITIONS -DRM_POSITIONAL_DEBUG)
    endif()
endif()

add_dependencies(${MumbleExeName} RmUpdater)

#[[
set(SHARED_SOURCES ${SHARED_SOURCE} ${SPEEX_SOURCES})
set(SHARED_LIBS Qt5::Gui Qt5::Network Qt5::Widgets Qt5::DBus Qt5::Xml Qt5::Sql ${Protobuf_LIBRARIES} crypto ssl)
set(SHARED_INCLUDES ${CMAKE_SOURCE_DIR}/src/ ${CMAKE_SOURCE_DIR}/src/ ${CMAKE_BINARY_DIR}/3rdparty/openssl/crypto ${CMAKE_BINARY_DIR}/3rdparty/openssl/ssl )
set(SHARED_DEFS -DUSE_NO_SRV)

#add_executable(RmMumble ${MUMBLE_SOURCES})
target_link_libraries(RmMumble PRIVATE RmShared ${ADDITIONAL_LIBS} speex opus Qt5::Svg Qt5::TextToSpeech)
target_include_directories(RmMumble
        PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}/src/mumble
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/mumble ${CMAKE_SOURCE_DIR}/src/mumble/widgets ${CMAKE_SOURCE_DIR}/3rdparty/qqbonjour-src
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src/mumble ${OPENSSL_INCLUDE_DIR} 3rdparty/smallft-src
        )

target_compile_definitions(RmMumble PRIVATE -DRESTRICT=__restrict__ -DMUMBLE -DNO_XINPUT2)
target_compile_definitions(RmShared PRIVATE -DMUMBLE)
]]
