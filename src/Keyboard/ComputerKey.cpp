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
    const std::string label,
    const Keyboard::KeyCode keyCode)
    : mX(x)
    , mY(y)
    , mWidth(width)
    , mHeight(height)
    , mLabel(std::move(label))
    , mKeyCode(keyCode)
{
}


const Property<int> & ComputerKey::x() const
{
    return mX;
}


const Property<int> & ComputerKey::y() const
{
    return mY;
}


const Property<unsigned int> & ComputerKey::width() const
{
    return mWidth;
}


const Property<unsigned int> & ComputerKey::height() const
{
    return mHeight;
}


const Property<std::string> & ComputerKey::label() const
{
    return mLabel;
}


const Property<Keyboard::KeyCode> & ComputerKey::keyCode() const
{
    return mKeyCode;
}

} // namespace KL
