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

#include "KL/Keyboard/ComputerKey.hpp"


namespace KL
{

ComputerKey::ComputerKey(const int x,
    const int y,
    const unsigned int width,
    const unsigned int height,
    std::string label,
    const Keyboard::KeyCode keyCode)
    : mX(x)
    , mY(y)
    , mWidth(width)
    , mHeight(height)
    , mLabel(std::move(label))
    , mKeyCode(keyCode)
{
}


int ComputerKey::x() const
{
    return mX;
}


int ComputerKey::y() const
{
    return mY;
}


unsigned int ComputerKey::width() const
{
    return mWidth;
}


unsigned int ComputerKey::height() const
{
    return mHeight;
}


const std::string & ComputerKey::label() const
{
    return mLabel;
}


Keyboard::KeyCode ComputerKey::keyCode() const
{
    return mKeyCode;
}


bool ComputerKey::operator==(const ComputerKey & other) const
{
    return mX == other.mX && mY == other.mY && mWidth == other.mWidth
        && mHeight == other.mHeight && mLabel == other.mLabel
        && mKeyCode == other.mKeyCode;
}

} // namespace KL
