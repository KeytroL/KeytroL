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

add_library(BaseKeytroLIO STATIC
    KeyboardInput.cpp
)

target_link_libraries(BaseKeytroLIO PUBLIC
    KeytroLCore
)


add_subdirectory(platform/default)

if (WIN32)
    add_subdirectory(platform/win)
    add_library(PlatformKeytroLIO ALIAS WinKeytroLIO)
else ()
    add_library(PlatformKeytroLIO ALIAS DefaultKeytroLIO)
endif ()


add_subdirectory(platform/mock)
add_subdirectory(test)
add_test(NAME KeytroLIO COMMAND KeytroLIOTest)
