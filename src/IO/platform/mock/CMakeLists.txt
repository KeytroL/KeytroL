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

add_library(MockKeytroLIO STATIC
    KeyboardInput.cpp
    MidiOut.cpp
    TestKeyboardInput.cpp
    TestMidiOut.cpp
)

target_include_directories(MockKeytroLIO PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(MockKeytroLIO PUBLIC
    BaseKeytroLIO
)

if (CMAKE_CXX_COMPILER_ID MATCHES Clang)
    target_compile_options(MockKeytroLIO PRIVATE
        -Wno-exit-time-destructors
    )
endif ()
