﻿cmake_minimum_required(VERSION 3.16)
project(uv_material_widgets)

include(cmake/uvsetup.cmake)
include(cmake/uvconfigmacros.cmake)

uv_initialize_build_flags()

add_subdirectory(src)
