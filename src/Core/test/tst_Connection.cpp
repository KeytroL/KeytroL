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

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <catch.hpp>
KL_RESTORE_WARNINGS


TEST_CASE("Construct a Connection, then assign it another Connection", "[Connection]")
{
    KL::Core::Connection connection;
    REQUIRE_FALSE(connection.isConnected());

    KL::Core::PrivateSignal<bool> signal;

    connection = signal.connect([](bool)
        {
        });
    REQUIRE(connection.isConnected());

    connection = KL::Core::Connection{};
    REQUIRE_FALSE(connection.isConnected());
}


TEST_CASE(
    "Construct a ScopedConnection, then assign it another Connection", "[Connection]")
{
    KL::Core::ScopedConnection scopedConnection;
    REQUIRE_FALSE(scopedConnection.isConnected());

    KL::Core::PrivateSignal<bool> signal;

    scopedConnection = signal.connect([](bool)
        {
        });
    REQUIRE(scopedConnection.isConnected());

    scopedConnection = KL::Core::ScopedConnection{};
    REQUIRE_FALSE(scopedConnection.isConnected());
}


TEST_CASE("Disconnect automatically with a ScopedConnection", "[Connection]")
{
    KL::Core::PrivateSignal<bool> signal;

    auto connection = signal.connect([](bool)
        {
        });
    REQUIRE(connection.isConnected());

    {
        KL::Core::ScopedConnection scopedConnection = connection;
        REQUIRE(scopedConnection.isConnected());
        REQUIRE(connection.isConnected());
    }

    REQUIRE_FALSE(connection.isConnected());
}
