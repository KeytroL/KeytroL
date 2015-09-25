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

#include "KL/Core/NotifyingVector.hpp"

#include "KL/Core/Warnings.hpp"

KL_DISABLE_WARNINGS
#include <catch.hpp>
KL_RESTORE_WARNINGS


TEST_CASE("Construct a NotifyingVector of integers", "[NotifyingVector]")
{
    SECTION("Default construction")
    {
        KL::NotifyingVector<int> ints;
        REQUIRE(ints.vector().size() == 0u);
    }

    SECTION("Construction from a std::vector")
    {
        KL::NotifyingVector<int> ints({1, 2, 3});
        REQUIRE(ints.vector().size() == 3u);
    }
}
