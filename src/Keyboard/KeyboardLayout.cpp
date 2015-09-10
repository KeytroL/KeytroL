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

#include <algorithm>


namespace KL
{

KeyboardLayout::KeyboardLayout()
    : mComputerKeys()
{
}


KeyboardLayout::ComputerKeyIterator KeyboardLayout::addComputerKey(
    const ComputerKey computerKey)
{
    const auto newComputerKeyAndBool =
        mComputerKeys.insert(std::unique_ptr<ComputerKey>{new ComputerKey(computerKey)});

    return newComputerKeyAndBool.first;
}


void KeyboardLayout::removeComputerKey(const ComputerKey & computerKey)
{
    auto foundComputerKey = std::find_if(mComputerKeys.begin(),
        mComputerKeys.end(),
        [&computerKey](const std::unique_ptr<ComputerKey> & ptr)
        {
            return (*ptr.get()) == computerKey;
        });

    if (foundComputerKey != mComputerKeys.end())
    {
        mComputerKeys.erase(foundComputerKey);
    }
}


const KeyboardLayout::ComputerKeySet & KeyboardLayout::computerKeys() const
{
    return mComputerKeys;
}

} // namespace KL
