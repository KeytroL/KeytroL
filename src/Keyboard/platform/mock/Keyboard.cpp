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

#include "KL/Keyboard/Keyboard.hpp"

#include "KeyboardPlatformImpl.hpp"
#include "TestKeyboard.hpp"


namespace KL
{

Keyboard::Keyboard()
{
    auto keyPressConnection = testing::TestKeyboard::instance().mKeyPressed.connect(
        [this](const KeyCode keyCode)
        {
            pressKey(keyCode);
        });

    auto keyReleaseConnection = testing::TestKeyboard::instance().mKeyReleased.connect(
        [this](const KeyCode keyCode)
        {
            releaseKey(keyCode);
        });

    mPlatformImpl = std::unique_ptr<PlatformImpl>(
        new PlatformImpl{keyPressConnection, keyReleaseConnection});
}


Keyboard::~Keyboard()
{
    mPlatformImpl->mKeyPressConnection.disconnect();
    mPlatformImpl->mKeyReleaseConnection.disconnect();
}

} // namespace KL