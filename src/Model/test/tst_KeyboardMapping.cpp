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

#include "KL/Model/KeyboardMapping.hpp"

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <catch.hpp>
KL_RESTORE_WARNINGS


TEST_CASE("Add a mapping to a KeyboardMapping", "[KeyboardMapping]")
{
    KL::Model::KeyboardMapping keyboardMapping;
    auto sentinel = 'a';

    keyboardMapping.at(2, KL::IO::KeyboardInput::KeyState::Pressed) = [&sentinel]()
    {
        sentinel = 'b';
    };
    REQUIRE(sentinel == 'a');

    const auto & readOnlyMapping = keyboardMapping;

    readOnlyMapping.at(2, KL::IO::KeyboardInput::KeyState::Pressed)();
    REQUIRE(sentinel == 'b');
}


TEST_CASE("Change a mapping in a KeyboardMapping", "[KeyboardMapping]")
{
    KL::Model::KeyboardMapping keyboardMapping;

    auto sentinel = 'a';

    keyboardMapping.at(2, KL::IO::KeyboardInput::KeyState::Pressed) = [&sentinel]()
    {
        sentinel = 'b';
    };
    REQUIRE(sentinel == 'a');

    keyboardMapping.at(2, KL::IO::KeyboardInput::KeyState::Pressed) = [&sentinel]()
    {
        sentinel = 'c';
    };
    REQUIRE(sentinel == 'a');

    keyboardMapping.at(2, KL::IO::KeyboardInput::KeyState::Pressed)();
    REQUIRE(sentinel == 'c');
}
