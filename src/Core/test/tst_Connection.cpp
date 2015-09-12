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

#include "KL/Core/Connection.hpp"

#include "KL/Core/Signal.hpp"
#include "KL/Core/Warnings.hpp"

KL_DISABLE_WARNINGS
#include <catch.hpp>
KL_RESTORE_WARNINGS


TEST_CASE("Construct a Connection, then assign it another Connection", "[Connection]")
{
    KL::Connection connection;
    REQUIRE_FALSE(connection.isConnected());

    KL::PrivateSignal<bool> signal;

    connection = signal.connect([](const bool)
        {
        });
    REQUIRE(connection.isConnected());

    connection = KL::Connection{};
    REQUIRE_FALSE(connection.isConnected());
}