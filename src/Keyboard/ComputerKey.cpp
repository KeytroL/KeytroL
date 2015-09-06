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

#include "KL/ComputerKey.hpp"


namespace KL
{

ComputerKey::ComputerKey(
    const int x, const int y, const unsigned int width, const unsigned int height)
    : mX(x)
    , mY(y)
    , mWidth(width)
    , mHeight(height)
    , mLabel(std::string())
    , mKeyCode(0)
{
}


Property<int> & ComputerKey::x()
{
    return mX;
}


const Property<int> & ComputerKey::x() const
{
    return mX;
}


Property<int> & ComputerKey::y()
{
    return mY;
}


const Property<int> & ComputerKey::y() const
{
    return mY;
}


Property<unsigned int> & ComputerKey::width()
{
    return mWidth;
}


const Property<unsigned int> & ComputerKey::width() const
{
    return mWidth;
}


Property<unsigned int> & ComputerKey::height()
{
    return mHeight;
}


const Property<unsigned int> & ComputerKey::height() const
{
    return mHeight;
}


Property<std::string> & ComputerKey::label()
{
    return mLabel;
}


const Property<std::string> & ComputerKey::label() const
{
    return mLabel;
}


Property<Keyboard::KeyCode> & ComputerKey::keyCode()
{
    return mKeyCode;
}


const Property<Keyboard::KeyCode> & ComputerKey::keyCode() const
{
    return mKeyCode;
}

} // namespace KL
