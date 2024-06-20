set(TARGET_NAME examples)

#add_definitions(-DQT_NO_DEBUG_OUTPUT)
#add_definitions(-DQT_NO_INFO_OUTPUT)
#add_definitions(-DQT_NO_WARNING_OUTPUT)
#add_definitions(-DQT_NO_CRITICAL_OUTPUT)
#add_definitions(-DQT_NO_FATAL_OUTPUT)

option(INSTALL_WITH_WINDOWS "Add WIN32 flag for executable during install" OFF)

include_directories(.)
include_directories(../components)

set(examples_SOURCES
        mainwidget.hpp
        mainwidget.cc
)

if (INSTALL_WITH_WINDOWS)
    add_executable(${TARGET_NAME}
            WIN32
            main.cc
            ${examples_SOURCES}
    )
else ()
    add_executable(${TARGET_NAME}
            main.cc
            ${examples_SOURCES}
    )
endif ()

target_link_libraries(${TARGET_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(${TARGET_NAME}
        uvappbarsettingseditor
        uvautocompletesettingseditor
        uvavatarsettingseditor
        uvbadgesettingseditor
        uvcheckboxsettingseditor
        uvcircularprogress
        uvfabsettingseditor
        uvflatbuttonsettingseditor
        uvdialogsettingseditor
        uvdrawersettingseditor
        uviconbuttonsettingseditor
        uvprogresssettingseditor
        uvradiobuttonsettingseditor
        uvscrollbarsettingseditor
        uvslidersettingseditor
        uvsnackbarsettingseditor
        uvtabssettingseditor
        uvtogglesettingseditor
        uvwatingwidgeteditor
        uvswitchbtnsettingseditor
        uvtoggleswitcheditor
        uvmessagebtnsettingseditor
)

install(TARGETS ${TARGET_NAME}
        RUNTIME DESTINATION bin
)

add_subdirectory(uvappbarsettingseditor)
add_subdirectory(uvautocompletesettingseditor)
add_subdirectory(uvavatarsettingseditor)
add_subdirectory(uvbadgesettingseditor)
add_subdirectory(uvcheckboxsettingseditor)
add_subdirectory(uvcircularprogresssettingseditor)
add_subdirectory(uvdialogsettingseditor)
add_subdirectory(uvdrawersettingseditor)
add_subdirectory(uvfabsettingseditor)
add_subdirectory(uvflatbuttonsettingseditor)
add_subdirectory(uviconbuttonsettingseditor)
add_subdirectory(uvprogresssettingseditor)
add_subdirectory(uvradiobuttonsettingseditor)
add_subdirectory(uvscrollbarsettingseditor)
add_subdirectory(uvslidersettingseditor)
add_subdirectory(uvsnackbarsettingseditor)
add_subdirectory(uvswitchbtnsettingseditor)
add_subdirectory(uvtabssettingseditor)
add_subdirectory(uvtogglesettingseditor)
add_subdirectory(uvtoggleswitchsettingseditor)
add_subdirectory(uvwatingwidgetsettingseditor)
add_subdirectory(uvmessagebtnsettingseditor)

#copy rcc file to execute directory
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/resource/resources.rcc
        $<TARGET_FILE_DIR:${TARGET_NAME}>
)