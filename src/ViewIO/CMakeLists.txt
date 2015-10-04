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

add_library(KeytroLViewIO STATIC
    ../../include/KL/ViewIO/KeyboardInput.hpp
    ../../include/KL/ViewIO/MidiOut.hpp
    ../../include/KL/ViewIO/MidiOutDevices.hpp
    KeyboardInput.cpp
    MidiOut.cpp
    MidiOutDevices.cpp
)

target_link_libraries(KeytroLViewIO PUBLIC
    BaseKeytroLIO
    Qt5::Core
)

set_target_properties(KeytroLViewIO PROPERTIES AUTOMOC ON)
set_target_properties(KeytroLViewIO PROPERTIES AUTOMOC_MOC_OPTIONS -bKL/MocWarnings.hpp)


find_package(Qt5Test 5.3)
if (Qt5Test_FOUND)
    add_subdirectory(test)
    add_test(NAME KeytroLViewIO COMMAND KeytroLViewIOTest)
endif ()
