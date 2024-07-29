cmake_minimum_required(VERSION 3.16)
project(uv_material_widgets)

include(cmake/uvsetup.cmake)
include(cmake/uvconfigmacros.cmake)

uv_initialize_build_flags()

uv_setup_Qt()

add_subdirectory(src)
add_subdirectory(examples)
