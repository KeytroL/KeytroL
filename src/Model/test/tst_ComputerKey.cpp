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