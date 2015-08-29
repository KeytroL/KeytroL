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

#include "KeyboardPlatformImpl.hpp"


namespace KL
{

Keyboard::PlatformImpl::PlatformImpl(const Keyboard & keyboard)
    : mKeyboard(keyboard)
{
}


void Keyboard::PlatformImpl::pressKey(Keyboard::KeyCode keyCode) const
{
    mKeyboard.pressKey(keyCode);
}


void Keyboard::PlatformImpl::releaseKey(Keyboard::KeyCode keyCode) const
{
    mKeyboard.releaseKey(keyCode);
}

} // namespace KL
