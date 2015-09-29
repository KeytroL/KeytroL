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

#include "KL/Core/Signal.hpp"

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <catch.hpp>
KL_RESTORE_WARNINGS


TEST_CASE("Connect to a Signal", "[Signal]")
{
    KL::Core::Signal<bool> signal;

    auto connection = signal.connect([](bool)
        {
        });

    REQUIRE(connection.isConnected());
}


TEST_CASE("Emit a Signal", "[Signal]")
{
    KL::Core::PrivateSignal<bool> signal;
    auto count = 0;

    signal.connect([&count](bool value)
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


TEST_CASE("Disconnect from a Signal", "[Signal]")
{
    KL::Core::PrivateSignal<bool> signal;
    auto count = 0;

    auto connection = signal.connect([&count](bool)
        {
            ++count;
        });
    REQUIRE(count == 0);
    REQUIRE(connection.isConnected());

    signal.emit(true);
    REQUIRE(count == 1);

    connection.disconnect();
    REQUIRE_FALSE(connection.isConnected());

    signal.emit(true);
    REQUIRE(count == 1);
}
