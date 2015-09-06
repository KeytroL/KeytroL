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

add_library(MockKeytroLKeyboard STATIC
    Keyboard.cpp
    KeyboardPlatformImpl.cpp
    TestKeyboard.cpp
)

target_include_directories(MockKeytroLKeyboard PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(MockKeytroLKeyboard PUBLIC
    BaseKeytroLKeyboard
)

if (CMAKE_CXX_COMPILER_ID MATCHES Clang)
    target_compile_options(MockKeytroLKeyboard PRIVATE
        -Wno-exit-time-destructors
    )
endif ()
