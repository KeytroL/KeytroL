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

#include "KL/Signal.hpp"

#include "KL/Warnings.hpp"

KL_DISABLE_WARNINGS
#include <catch.hpp>
KL_RESTORE_WARNINGS


TEST_CASE("Connect to a Signal", "[Signal]")
{
    KL::Signal<bool> signal;

    auto connection = signal.connect([](const bool)
        {
        });
}


TEST_CASE("Emit a Signal", "[Signal]")
{
    KL::PrivateSignal<bool> signal;
    auto count = 0;

    signal.connect([&count](const bool value)
        {
            if (value)
            {
                ++count;
            }
        });
    REQUIRE(count == 0);

    signal.emit(true);
    REQUIRE(count == 1);

    signal.emit(false);
    REQUIRE(count == 1);
}
