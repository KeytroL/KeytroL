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

add_library(Catch STATIC
    CatchMain.cpp
)

target_include_directories(Catch PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

if (CMAKE_CXX_COMPILER_ID MATCHES Clang)
    target_compile_options(Catch INTERFACE
        -Wno-global-constructors
        -Wno-unused-variable
    )
    target_compile_options(Catch PUBLIC
        -Wno-exit-time-destructors
    )
elseif (MSVC)
    target_compile_options(Catch PRIVATE
        /wd4242 # 'identifier' : conversion from 'type1' to 'type2', possible loss of data
    )
endif ()
