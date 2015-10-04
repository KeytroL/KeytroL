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

#include "KL/Model/ComputerKey.hpp"

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <catch.hpp>
KL_RESTORE_WARNINGS


TEST_CASE("Construct a ComputerKey", "[ComputerKey]")
{
    const KL::Model::ComputerKey computerKey(23, 42, 8, 7, "A", 2);

    REQUIRE(computerKey.x() == 23);
    REQUIRE(computerKey.y() == 42);
    REQUIRE(computerKey.width() == 8);
    REQUIRE(computerKey.height() == 7);
    REQUIRE(computerKey.label() == "A");
    REQUIRE(computerKey.keyCode() == 2);
}


TEST_CASE("Construct a ComputerKey from another one and a new position", "[ComputerKey]")
{
    const KL::Model::ComputerKey first(23, 42, 8, 7, "A", 2);

    const KL::Model::ComputerKey second(first, -32, -24);

    REQUIRE(second.x() == -32);
    REQUIRE(second.y() == -24);
    REQUIRE(second.width() == first.width());
    REQUIRE(second.height() == first.height());
    REQUIRE(second.label() == first.label());
    REQUIRE(second.keyCode() == first.keyCode());
}


TEST_CASE("Construct a ComputerKey from another one and a new label", "[ComputerKey]")
{
    const KL::Model::ComputerKey first(23, 42, 8, 7, "A", 2);

    const KL::Model::ComputerKey second(first, "B");

    REQUIRE(second.x() == first.x());
    REQUIRE(second.y() == first.y());
    REQUIRE(second.width() == first.width());
    REQUIRE(second.height() == first.height());
    REQUIRE(second.label() == "B");
    REQUIRE(second.keyCode() == first.keyCode());
}


TEST_CASE("Construct a ComputerKey from another one and a new key code", "[ComputerKey]")
{
    const KL::Model::ComputerKey first(23, 42, 8, 7, "A", 2);

    const KL::Model::ComputerKey second(first, 0);

    REQUIRE(second.x() == first.x());
    REQUIRE(second.y() == first.y());
    REQUIRE(second.width() == first.width());
    REQUIRE(second.height() == first.height());
    REQUIRE(second.label() == first.label());
    REQUIRE(second.keyCode() == 0);
}


TEST_CASE("Compare two ComputerKeys that are equal", "[ComputerKey]")
{
    const KL::Model::ComputerKey first(23, 42, 8, 7, "A", 2);
    const KL::Model::ComputerKey second(23, 42, 8, 7, "A", 2);

    REQUIRE(first == second);
}


TEST_CASE("Compare two ComputerKeys that are not equal", "[ComputerKey]")
{
    const KL::Model::ComputerKey first(23, 42, 8, 7, "A", 2);
    KL::Model::ComputerKey second(23, 42, 8, 7, "A", 2);

    SECTION("because they have different x")
    {
        second = KL::Model::ComputerKey(-32, 42, 8, 7, "A", 2);
        REQUIRE(second.x() != first.x());
    }

    SECTION("because they have different y")
    {
        second = KL::Model::ComputerKey(23, -24, 8, 7, "A", 2);
        REQUIRE(second.y() != first.y());
    }

    SECTION("because they have different width")
    {
        second = KL::Model::ComputerKey(23, 42, 4, 7, "A", 2);
        REQUIRE(second.width() != first.width());
    }

    SECTION("because they have different height")
    {
        second = KL::Model::ComputerKey(23, 42, 8, 4, "A", 2);
        REQUIRE(second.height() != first.height());
    }

    SECTION("because they have different label")
    {
        second = KL::Model::ComputerKey(23, 42, 8, 7, "B", 2);
        REQUIRE(second.label() != first.label());
    }

    SECTION("because they have different keyCode")
    {
        second = KL::Model::ComputerKey(23, 42, 8, 7, "A", 0);
        REQUIRE(second.keyCode() != first.keyCode());
    }

    REQUIRE_FALSE(first == second);
}
