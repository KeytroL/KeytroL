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

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)


project(KeytroL VERSION 0.1.0)


if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 11)
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(
        -Werror -Weverything
    )

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(
        /WX /W4 /Wall
        /wd4514 /wd4710 /wd4711 # inlining information
        /wd4350 /wd4571 /wd4640 # obsolete
        /wd4625 /wd4626 # implicitly defined as deleted
        /wd4820 # padding
    )

    if (MSVC_VERSION VERSION_GREATER "1800")
        add_compile_options(
            /wd5026 /wd5027 # implicitly defined as deleted
        )
    endif ()
endif ()


add_subdirectory(src/KeytroLCore)
add_subdirectory(src/KeytroLCore/test)

add_subdirectory(third-party/Catch)


enable_testing()
add_test(NAME KeytroLCore COMMAND KeytroLCoreTest)
