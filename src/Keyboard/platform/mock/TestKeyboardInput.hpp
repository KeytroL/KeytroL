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


namespace KL
{

class TestKeyboardInput
{
public:
    static TestKeyboardInput & instance();

    void pressKey(KeyboardInput::KeyCode keyCode) const;
    void releaseKey(KeyboardInput::KeyCode keyCode) const;

private:
    TestKeyboardInput() = default;

    friend class KL::KeyboardInput;

    PrivateSignal<KeyboardInput::KeyCode> mKeyPressed;
    PrivateSignal<KeyboardInput::KeyCode> mKeyReleased;
};

} // namespace KL
