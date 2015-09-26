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

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <catch.hpp>
KL_RESTORE_WARNINGS


TEST_CASE("Construct a KeyboardLayout", "[KeyboardLayout]")
{
    KL::KeyboardLayout keyboardLayout;

    REQUIRE(keyboardLayout.computerKeys().size() == 0u);
}


TEST_CASE("Add a ComputerKey to a KeyboardLayout", "[KeyboardLayout]")
{
    KL::KeyboardLayout keyboardLayout;

    keyboardLayout.addComputerKey(KL::ComputerKey(23, 42, 8, 7, "", 0));

    REQUIRE(keyboardLayout.computerKeys().size() == 1u);
    REQUIRE(keyboardLayout.computerKeys().begin()->y() == 42);
}


TEST_CASE("Remove a ComputerKey from a KeyboardLayout", "[KeyboardLayout]")
{
    KL::KeyboardLayout keyboardLayout;

    keyboardLayout.addComputerKey(KL::ComputerKey(23, 42, 8, 7, "", 0));
    REQUIRE(keyboardLayout.computerKeys().size() == 1u);

    keyboardLayout.removeComputerKey(0);
    REQUIRE(keyboardLayout.computerKeys().size() == 0u);
}
