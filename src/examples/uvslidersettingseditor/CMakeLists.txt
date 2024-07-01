set(TARGET_NAME uvslidersettingseditor)

if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

include_directories(../../components)
aux_source_directory(. SRC_LIST)

add_library(${TARGET_NAME} SHARED ${SRC_LIST})
target_link_libraries(${TARGET_NAME} Qt5::Widgets)
target_link_libraries(${TARGET_NAME} uvmaterialslider)

target_compile_definitions(${TARGET_NAME} PRIVATE CUVSLIDERSETTINGSEDITOR_LIB)

uv_install_dll()