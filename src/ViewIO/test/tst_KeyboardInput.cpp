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

#include "KL/ViewIO/KeyboardInput.hpp"

#include "TestKeyboardInput.hpp"

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <catch.hpp>
#include <QtTest/QSignalSpy>
KL_RESTORE_WARNINGS


TEST_CASE("Emits a signal when a physical key is pressed", "[KeyboardInput]")
{
    KL::ViewIO::KeyboardInput keyboardInput;
    QSignalSpy keyPressedSpy{&keyboardInput, SIGNAL(keyPressed(unsigned int))};

    KL::IO::TestKeyboardInput::instance().pressKey(42);

    REQUIRE(keyPressedSpy.count() == 1);
    REQUIRE(keyPressedSpy.front().at(0) == 42);
}


TEST_CASE("Emits a signal when a physical key is released", "[KeyboardInput]")
{
    KL::ViewIO::KeyboardInput keyboardInput;
    QSignalSpy keyReleasedSpy{&keyboardInput, SIGNAL(keyReleased(unsigned int))};

    KL::IO::TestKeyboardInput::instance().releaseKey(23);

    REQUIRE(keyReleasedSpy.count() == 1);
    REQUIRE(keyReleasedSpy.front().at(0) == 23);
}
