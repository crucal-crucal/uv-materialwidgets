set(TARGET_NAME example)

#add_definitions(-DQT_NO_DEBUG_OUTPUT)
#add_definitions(-DQT_NO_INFO_OUTPUT)
#add_definitions(-DQT_NO_WARNING_OUTPUT)
#add_definitions(-DQT_NO_CRITICAL_OUTPUT)
#add_definitions(-DQT_NO_FATAL_OUTPUT)

include_directories(.)
include_directories(../src)

set(examples_SOURCES
        mainwidget.hpp
        mainwidget.cc
)

add_executable(${TARGET_NAME}
        main.cc
        ${examples_SOURCES}
)

target_link_libraries(${TARGET_NAME} Qt5::Widgets)
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
        uvcomboboxsettingseditor
        uvstackwidgetsettingseditor
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
add_subdirectory(uvcomboboxsettingseditor)
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
add_subdirectory(uvstackwidgetsettingseditor)

#copy rcc file to execute directory
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/resource/resources.rcc
        $<TARGET_FILE_DIR:${TARGET_NAME}>
)

set_target_properties(${TARGET_NAME} PROPERTIES
        WIN32_EXECUTABLE FALSE
)