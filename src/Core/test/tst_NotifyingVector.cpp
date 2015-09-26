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

#include "KL/Warnings.hpp"
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


TEST_CASE("Fail to replace elements in a NotifyingVector", "[NotifyingVector]")
{
    KL::NotifyingVector<int> ints({1, 2, 3});

    SECTION("When first > last")
    {
        REQUIRE_THROWS_AS(ints.replace(2, 1, {}), std::invalid_argument);
    }

    SECTION("When last > size")
    {
        REQUIRE_THROWS_AS(ints.replace(2, 4, {}), std::invalid_argument);
    }
}


TEST_CASE("Increase number of elements in a NotifyingVector", "[NotifyingVector]")
{
    KL::NotifyingVector<int> ints({1, 2, 3});

    SECTION("By inserting one new element")
    {
        ints.replace(1, 1, {4});
        REQUIRE(ints.vector() == std::vector<int>({1, 4, 2, 3}));
    }

    SECTION("By inserting several new elements")
    {
        ints.replace(3, 3, {4, 5});
        REQUIRE(ints.vector() == std::vector<int>({1, 2, 3, 4, 5}));
    }

    SECTION("By inserting new elements and replacing elements")
    {
        ints.replace(2, 3, {4, 5});
        REQUIRE(ints.vector() == std::vector<int>({1, 2, 4, 5}));
    }
}


TEST_CASE("Decrease number of elements in a NotifyingVector", "[NotifyingVector]")
{
    KL::NotifyingVector<int> ints({1, 2, 3});

    SECTION("By clearing the container")
    {
        ints.replace(0, 3, {});
        REQUIRE(ints.vector().size() == 0u);
    }

    SECTION("By erasing one element")
    {
        ints.replace(1, 2, {});
        REQUIRE(ints.vector() == std::vector<int>({1, 3}));
    }

    SECTION("By erasing and replacing elements")
    {
        ints.replace(0, 2, {4});
        REQUIRE(ints.vector() == std::vector<int>({4, 3}));
    }
}


TEST_CASE("Keep same number of elements in a NotifyingVector", "[NotifyingVector]")
{
    KL::NotifyingVector<int> ints({1, 2, 3});

    SECTION("By replacing no elements")
    {
        ints.replace(2, 2, {});
        REQUIRE(ints.vector() == std::vector<int>({1, 2, 3}));
    }

    SECTION("By replacing one element")
    {
        ints.replace(0, 1, {4});
        REQUIRE(ints.vector() == std::vector<int>({4, 2, 3}));
    }

    SECTION("By replacing several elements")
    {
        ints.replace(1, 3, {4, 5});
        REQUIRE(ints.vector() == std::vector<int>({1, 4, 5}));
    }
}


TEST_CASE("Observe replacements in a NotifyingVector", "[NotifyingVector]")
{
    KL::NotifyingVector<int> ints({1, 2, 3});

    auto testNotification =
        [](const KL::NotifyingVector<int>::Notification & notification)
    {
        REQUIRE(notification.first == 0u);
        REQUIRE(notification.last == 1u);
        REQUIRE(notification.replacementSize == 2u);
    };

    ints.beforeReplace().connect(testNotification);
    ints.afterReplace().connect(testNotification);

    ints.replace(0, 1, {4, 2});

    REQUIRE(ints.vector() == std::vector<int>({4, 2, 2, 3}));
}
