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

#pragma once

#include "KL/Keyboard.hpp"
#include "KL/Property.hpp"

#include <string>


namespace KL
{

class ComputerKey
{
public:
    ComputerKey(int x, int y, unsigned int width, unsigned int height);

    Property<int> & x();
    const Property<int> & x() const;

    Property<int> & y();
    const Property<int> & y() const;

    Property<unsigned int> & width();
    const Property<unsigned int> & width() const;

    Property<unsigned int> & height();
    const Property<unsigned int> & height() const;

    Property<std::string> & label();
    const Property<std::string> & label() const;

    Property<Keyboard::KeyCode> & keyCode();
    const Property<Keyboard::KeyCode> & keyCode() const;

private:
    Property<int> mX;
    Property<int> mY;
    Property<unsigned int> mWidth;
    Property<unsigned int> mHeight;
    Property<std::string> mLabel;
    Property<Keyboard::KeyCode> mKeyCode;
};

} // namespace KL
