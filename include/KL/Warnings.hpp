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

#if defined(__clang__)

    #define KL_DISABLE_WARNINGS \
        _Pragma("clang diagnostic push") \
        _Pragma("clang diagnostic ignored \"-Wconversion\"") \
        _Pragma("clang diagnostic ignored \"-Wcovered-switch-default\"") \
        _Pragma("clang diagnostic ignored \"-Wdeprecated\"") \
        _Pragma("clang diagnostic ignored \"-Wdisabled-macro-expansion\"") \
        _Pragma("clang diagnostic ignored \"-Wdocumentation-unknown-command\"") \
        _Pragma("clang diagnostic ignored \"-Wexit-time-destructors\"") \
        _Pragma("clang diagnostic ignored \"-Wfloat-equal\"") \
        _Pragma("clang diagnostic ignored \"-Wsign-conversion\"") \
        _Pragma("clang diagnostic ignored \"-Wundefined-reinterpret-cast\"") \
        _Pragma("clang diagnostic ignored \"-Wused-but-marked-unused\"") \
        /**/

    #define KL_RESTORE_WARNINGS \
        _Pragma("clang diagnostic pop")

#elif defined(__GNUC__)

    #define KL_DISABLE_WARNINGS \
        _Pragma("GCC diagnostic push") \
        /**/

    #define KL_RESTORE_WARNINGS \
        _Pragma("GCC diagnostic pop")

#elif defined(_MSC_VER)

    #define KL_DISABLE_WARNINGS \
        __pragma(warning(push)) \
        __pragma(warning(disable: 4061)) \
        __pragma(warning(disable: 4127)) \
        __pragma(warning(disable: 4244)) \
        __pragma(warning(disable: 4251)) \
        __pragma(warning(disable: 4267)) \
        __pragma(warning(disable: 4365)) \
        __pragma(warning(disable: 4371)) \
        __pragma(warning(disable: 4619)) \
        __pragma(warning(disable: 4668)) \
        __pragma(warning(disable: 4702)) \
        __pragma(warning(disable: 4800)) \
        /**/

    #define KL_RESTORE_WARNINGS \
        __pragma(warning(pop))

#else

    #error This compiler is not supported.

#endif

// clang-format on
