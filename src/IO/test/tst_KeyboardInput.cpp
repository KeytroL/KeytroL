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

#include "KL/IO/KeyboardInput.hpp"

#include "TestKeyboardInput.hpp"

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <catch.hpp>
KL_RESTORE_WARNINGS


TEST_CASE("Press a key", "[KeyboardInput]")
{
    KL::IO::KeyboardInput keyboardInput;
    auto count = 0;

    keyboardInput.keyPressed().connect([&count](KL::IO::KeyboardInput::KeyCode keyCode)
                                       {
                                           if (keyCode == 42)
                                           {
                                               ++count;
                                           }
                                       });
    REQUIRE(count == 0);

    KL::IO::TestKeyboardInput::instance().pressKey(42);
    REQUIRE(count == 1);
}


TEST_CASE("Release a key", "[KeyboardInput]")
{
    KL::IO::KeyboardInput keyboardInput;
    auto count = 0;

    keyboardInput.keyReleased().connect([&count](KL::IO::KeyboardInput::KeyCode keyCode)
                                        {
                                            if (keyCode == 23)
                                            {
                                                ++count;
                                            }
                                        });
    REQUIRE(count == 0);

    KL::IO::TestKeyboardInput::instance().releaseKey(23);
    REQUIRE(count == 1);
}
