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

add_library(BaseKeytroLCore STATIC
    IKeyboard.cpp
)

target_include_directories(BaseKeytroLCore PUBLIC ${PROJECT_SOURCE_DIR}/include)


add_subdirectory(platform/default)

add_library(KeytroLCore ALIAS DefaultKeytroLCore)


add_subdirectory(test)
