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

include(ExternalProject)

add_library(Catch INTERFACE)

ExternalProject_Add(
    EP_Catch
    GIT_REPOSITORY https://github.com/philsquared/Catch
    GIT_TAG v1.2.1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

if (NOT CMAKE_VERSION VERSION_LESS "3.3")
    add_dependencies(Catch EP_Catch)
endif ()

ExternalProject_Get_Property(EP_Catch SOURCE_DIR)
target_include_directories(Catch INTERFACE ${SOURCE_DIR}/include)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(Catch INTERFACE
        /wd4242 # 'identifier' : conversion from 'type1' to 'type2', possible loss of data
    )

endif ()
