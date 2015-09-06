// KeytroL
// Copyright (C) 2015 Alain Martin
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

#pragma once

// clang-format off

#if defined(_MSC_VER)

    #define KL_DISABLE_WARNINGS \
        __pragma(warning(push)) \
        __pragma(warning(disable: 4061)) \
        __pragma(warning(disable: 4127)) \
        __pragma(warning(disable: 4365)) \
        __pragma(warning(disable: 4371)) \
        __pragma(warning(disable: 4619)) \
        __pragma(warning(disable: 4668)) \
        __pragma(warning(disable: 4702))

    #define KL_RESTORE_WARNINGS \
        __pragma(warning(pop))

#else

    #define KL_DISABLE_WARNINGS
    #define KL_RESTORE_WARNINGS

#endif

// clang-format on
