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

#include "KL/Keyboard/Keyboard.hpp"

#include <string>


namespace KL
{

class ComputerKey
{
public:
    ComputerKey(int x,
        int y,
        unsigned int width,
        unsigned int height,
        std::string label,
        Keyboard::KeyCode keyCode);

    ComputerKey(const ComputerKey & other) = default;
    ComputerKey(const ComputerKey & other, int x, int y);

    ComputerKey(ComputerKey && other);
    ComputerKey & operator=(ComputerKey && other);

    int x() const;
    int y() const;

    unsigned int width() const;
    unsigned int height() const;

    const std::string & label() const;

    Keyboard::KeyCode keyCode() const;

    bool operator==(const ComputerKey & other) const;

private:
    int mX;
    int mY;

    unsigned int mWidth;
    unsigned int mHeight;

    std::string mLabel;

    Keyboard::KeyCode mKeyCode;
};

} // namespace KL
