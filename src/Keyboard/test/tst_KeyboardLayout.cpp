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

#include "KL/Keyboard/KeyboardLayout.hpp"

#include "KL/Core/Warnings.hpp"

KL_DISABLE_WARNINGS
#include <catch.hpp>
KL_RESTORE_WARNINGS


TEST_CASE("Construct a KeyboardLayout", "[KeyboardLayout]")
{
    const KL::KeyboardLayout keyboardLayout;

    REQUIRE(keyboardLayout.computerKeys().size() == 0u);
}


TEST_CASE("Add a ComputerKey to a KeyboardLayout", "[KeyboardLayout]")
{
    KL::KeyboardLayout keyboardLayout;

    keyboardLayout.addComputerKey(KL::ComputerKey(23, 42, 8, 7, "", 0));

    REQUIRE(keyboardLayout.computerKeys().size() == 1u);
    REQUIRE(keyboardLayout.computerKeys().begin()->y() == 42);
}


TEST_CASE("React to adding a ComputerKey to a KeyboardLayout", "[KeyboardLayout]")
{
    KL::KeyboardLayout keyboardLayout;
    keyboardLayout.addComputerKey(KL::ComputerKey(23, 42, 8, 7, "", 0));

    KL::KeyboardLayout::SizeType aboutToBeAdded = 0u;
    KL::KeyboardLayout::SizeType added = 0u;

    keyboardLayout.computerKeyAboutToBeAdded().connect(
        [&aboutToBeAdded](const KL::KeyboardLayout::SizeType index)
        {
            aboutToBeAdded = index;
        });
    REQUIRE(aboutToBeAdded == 0u);

    keyboardLayout.computerKeyAdded().connect(
        [&added](const KL::KeyboardLayout::SizeType index)
        {
            added = index;
        });
    REQUIRE(added == 0u);

    keyboardLayout.addComputerKey(KL::ComputerKey(23, 42, 8, 7, "", 0));
    REQUIRE(aboutToBeAdded == 1u);
    REQUIRE(added == 1u);
    REQUIRE(keyboardLayout.computerKeys().size() == 2u);
}


TEST_CASE("Remove a ComputerKey from a KeyboardLayout", "[KeyboardLayout]")
{
    KL::KeyboardLayout keyboardLayout;

    keyboardLayout.addComputerKey(KL::ComputerKey(23, 42, 8, 7, "", 0));
    REQUIRE(keyboardLayout.computerKeys().size() == 1u);

    keyboardLayout.removeComputerKey(KL::ComputerKey(23, 42, 8, 7, "", 0));
    REQUIRE(keyboardLayout.computerKeys().size() == 0u);
}


TEST_CASE("React to removing a ComputerKey from a KeyboardLayout", "[KeyboardLayout]")
{
    KL::KeyboardLayout keyboardLayout;
    keyboardLayout.addComputerKey(KL::ComputerKey(0, 0, 0, 0, "", 0));
    keyboardLayout.addComputerKey(KL::ComputerKey(1, 1, 1, 1, "", 0));

    KL::KeyboardLayout::SizeType aboutToBeRemoved = 0u;
    KL::KeyboardLayout::SizeType removed = 0u;

    keyboardLayout.computerKeyAboutToBeRemoved().connect(
        [&aboutToBeRemoved](const KL::KeyboardLayout::SizeType index)
        {
            aboutToBeRemoved = index;
        });
    REQUIRE(aboutToBeRemoved == 0u);

    keyboardLayout.computerKeyRemoved().connect(
        [&removed](const KL::KeyboardLayout::SizeType index)
        {
            removed = index;
        });
    REQUIRE(removed == 0u);

    keyboardLayout.removeComputerKey(KL::ComputerKey(1, 1, 1, 1, "", 0));
    REQUIRE(aboutToBeRemoved == 1u);
    REQUIRE(removed == 1u);
    REQUIRE(keyboardLayout.computerKeys().size() == 1u);
}
