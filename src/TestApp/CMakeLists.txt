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

add_executable(KeytroLTestApp
    KeyboardLayoutViewModel.cpp
    main.cpp
    ViewKeyboardInput.cpp
    ViewMidiOut.cpp
    ViewMidiOutDevices.cpp
    XmlKeyboardLayout.cpp
)

target_link_libraries(KeytroLTestApp PRIVATE
    KeytroLKeyboard
    KeytroLMidi
    Qt5::Quick
)

set_target_properties(KeytroLTestApp PROPERTIES AUTOMOC ON)
set_target_properties(KeytroLTestApp PROPERTIES AUTOMOC_MOC_OPTIONS -bMocWarnings.hpp)

target_include_directories(KeytroLTestApp PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_compile_definitions(KeytroLTestApp PRIVATE
    QML_MAIN="${CMAKE_CURRENT_LIST_DIR}/main.qml"
)
