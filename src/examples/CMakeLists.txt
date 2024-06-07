set(TARGET_NAME examples)

setupQt()

include_directories(.)
include_directories(../components)

set(examples_SOURCES
        mainwidget.hpp
        mainwidget.cc
)

add_executable(${TARGET_NAME}
        main.cc
        ${examples_SOURCES}
)

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
add_subdirectory(uvtabssettingseditor)
add_subdirectory(uvtogglesettingseditor)
add_subdirectory(uvwatingwidgetsettingseditor)

#copy rcc file to execute directory
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/resource/resources.rcc
        $<TARGET_FILE_DIR:${TARGET_NAME}>
)