#  KeytroL
#  Copyright (C) 2015 Alain Martin
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)


project(KeytroL VERSION 0.1.0)


if (CMAKE_CXX_COMPILER_ID MATCHES Clang)
    add_compile_options(
        -std=c++11
        -Werror -Weverything
        -Wno-c++98-compat
        -Wno-padded
    )
elseif (CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(
        -std=c++11
        -Werror -Wall -Wextra -pedantic
    )
elseif (MSVC)
    add_compile_options(
        /WX /W4 /Wall
        /wd4265 # from standard headers
        /wd4350 /wd4571 /wd4640 # obsolete
        /wd4512 # could not be generated
        /wd4514 /wd4710 /wd4711 # inlining information
        /wd4625 /wd4626 # implicitly defined as deleted
        /wd4820 # padding
    )

    if (MSVC_VERSION VERSION_GREATER 1800)
        add_compile_options(
            /wd5026 /wd5027 # implicitly defined as deleted
        )
    endif ()
endif ()


include_directories(${PROJECT_SOURCE_DIR}/include)

enable_testing()
add_subdirectory(third-party/Catch)

add_subdirectory(src/Core)
add_subdirectory(src/Keyboard)
add_subdirectory(src/Midi)

find_package(Qt5Widgets)
if (Qt5Widgets_FOUND)
    add_subdirectory(src/TestApp)
endif ()
