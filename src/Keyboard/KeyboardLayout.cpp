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

#include "KL/Keyboard/KeyboardLayout.hpp"


namespace KL
{

KeyboardLayout::KeyboardLayout()
    : mComputerKeys()
{
}


KeyboardLayout::ComputerKeyIterator KeyboardLayout::addComputerKey(
    int x, int y, unsigned int width, unsigned int height)
{
    const auto newComputerKeyAndBool = mComputerKeys.insert(
        std::unique_ptr<ComputerKey>{new ComputerKey(x, y, width, height)});

    return newComputerKeyAndBool.first;
}


void KeyboardLayout::removeComputerKey(ComputerKeyIterator computerKeyIt)
{
    mComputerKeys.erase(computerKeyIt);
}


const KeyboardLayout::ComputerKeySet & KeyboardLayout::computerKeys() const
{
    return mComputerKeys;
}

} // namespace KL
