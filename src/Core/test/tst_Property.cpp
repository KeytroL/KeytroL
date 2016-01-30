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

#include "KL/Core/Property.hpp"

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <catch.hpp>
KL_RESTORE_WARNINGS


TEST_CASE("Construct a char Property", "[Property]")
{
    const KL::Core::Property<char> property{'a'};

    REQUIRE(property.value() == 'a');
}


TEST_CASE("Modify a char Property", "[Property]")
{
    KL::Core::Property<char> property{'a'};
    auto sentinel = 'b';

    property.valueChanged().connect([&sentinel](char value)
                                    {
                                        sentinel = value;
                                    });

    REQUIRE(sentinel == 'b');

    property.setValue('c');
    REQUIRE(sentinel == 'c');
}
