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

#include "KL/IKeyboard.hpp"


namespace KL
{

Signal<IKeyboard::KeyCode> & IKeyboard::keyPressed()
{
    return mKeyPressed;
}


Signal<IKeyboard::KeyCode> & IKeyboard::keyReleased()
{
    return mKeyReleased;
}


void IKeyboard::pressKey(const IKeyboard::KeyCode keyCode) const
{
    mKeyPressed.emit(keyCode);
}


void IKeyboard::releaseKey(const IKeyboard::KeyCode keyCode) const
{
    mKeyReleased.emit(keyCode);
}

} // namespace KL
