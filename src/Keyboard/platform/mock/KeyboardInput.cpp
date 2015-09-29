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

#include "KL/Keyboard/KeyboardInput.hpp"

#include "KeyboardInputPlatformImpl.hpp"
#include "TestKeyboardInput.hpp"


namespace KL
{

KeyboardInput::KeyboardInput()
{
    auto keyPressConnection =
        TestKeyboardInput::instance().mKeyPressed.connect([this](KeyCode keyCode)
            {
                pressKey(keyCode);
            });

    auto keyReleaseConnection =
        TestKeyboardInput::instance().mKeyReleased.connect([this](KeyCode keyCode)
            {
                releaseKey(keyCode);
            });

    mPlatformImpl = std::unique_ptr<PlatformImpl>(
        new PlatformImpl{std::move(keyPressConnection), std::move(keyReleaseConnection)});
}


KeyboardInput::~KeyboardInput() = default;

} // namespace KL
