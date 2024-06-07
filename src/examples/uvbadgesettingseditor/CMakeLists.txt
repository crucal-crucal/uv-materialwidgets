set(TARGET_NAME uvbadgesettingseditor)

if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

include_directories(../../components)
aux_source_directory(. SRC_LIST)

add_library(${TARGET_NAME} SHARED ${SRC_LIST})
target_link_libraries(${TARGET_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries(${TARGET_NAME} uvmaterialbadge uvmaterialavatar)

target_compile_definitions(${TARGET_NAME} PRIVATE CUVBADGESETTINGSEDITOR_LIB)

installdll()