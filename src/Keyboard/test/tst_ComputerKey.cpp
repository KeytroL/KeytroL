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

#include "KL/Keyboard/ComputerKey.hpp"

#include "KL/Core/Warnings.hpp"

KL_DISABLE_WARNINGS
#include <catch.hpp>
KL_RESTORE_WARNINGS


TEST_CASE("Construct a ComputerKey", "[ComputerKey]")
{
    const KL::ComputerKey computerKey(23, 42, 8, 7, "A", 2);

    REQUIRE(computerKey.x().value() == 23);
    REQUIRE(computerKey.y().value() == 42);
    REQUIRE(computerKey.width().value() == 8);
    REQUIRE(computerKey.height().value() == 7);
    REQUIRE(computerKey.label().value() == "A");
    REQUIRE(computerKey.keyCode().value() == 2);
}
