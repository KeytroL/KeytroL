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

#include "TestKeyboard.hpp"


namespace KL
{
namespace testing
{

TestKeyboard & TestKeyboard::instance()
{
    static TestKeyboard testKeyboard;
    return testKeyboard;
}


void TestKeyboard::pressKey(Keyboard::KeyCode keyCode) const
{
    mKeyPressed.emit(keyCode);
}


void TestKeyboard::releaseKey(Keyboard::KeyCode keyCode) const
{
    mKeyReleased.emit(keyCode);
}

} // namespace testing
} // namespace KL
