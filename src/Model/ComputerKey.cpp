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

#include "KL/Model/ComputerKey.hpp"


namespace KL
{
namespace Model
{

ComputerKey::ComputerKey(int x,
    int y,
    unsigned int width,
    unsigned int height,
    std::string label,
    IO::KeyboardInput::KeyCode keyCode)
    : mValues(std::make_shared<ComputerKeyValues>(
          ComputerKeyValues{x, y, width, height, std::move(label), keyCode}))
{
}


ComputerKey::ComputerKey(const ComputerKey & other, int x, int y)
    : mValues(std::make_shared<ComputerKeyValues>(ComputerKeyValues{
          x, y, other.width(), other.height(), other.label(), other.keyCode()}))
{
}


ComputerKey::ComputerKey(const ComputerKey & other, std::string label)
    : mValues(std::make_shared<ComputerKeyValues>(ComputerKeyValues{other.x(),
          other.y(),
          other.width(),
          other.height(),
          std::move(label),
          other.keyCode()}))
{
}


ComputerKey::ComputerKey(const ComputerKey & other, IO::KeyboardInput::KeyCode keyCode)
    : mValues(std::make_shared<ComputerKeyValues>(ComputerKeyValues{
          other.x(), other.y(), other.width(), other.height(), other.label(), keyCode}))
{
}


ComputerKey::ComputerKey(ComputerKey && other)
    : mValues(std::move(other.mValues))
{
}


ComputerKey & ComputerKey::operator=(ComputerKey && other)
{
    mValues = std::move(other.mValues);
    return *this;
}


int ComputerKey::x() const
{
    return mValues->x;
}


int ComputerKey::y() const
{
    return mValues->y;
}


unsigned int ComputerKey::width() const
{
    return mValues->width;
}


unsigned int ComputerKey::height() const
{
    return mValues->height;
}


const std::string & ComputerKey::label() const
{
    return mValues->label;
}


IO::KeyboardInput::KeyCode ComputerKey::keyCode() const
{
    return mValues->keyCode;
}


bool ComputerKey::operator==(const ComputerKey & other) const
{
    return mValues == other.mValues
        || (mValues->x == other.mValues->x && mValues->y == other.mValues->y
               && mValues->width == other.mValues->width
               && mValues->height == other.mValues->height
               && mValues->label == other.mValues->label
               && mValues->keyCode == other.mValues->keyCode);
}

} // namespace Model
} // namespace KL
