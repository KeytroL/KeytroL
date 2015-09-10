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


void KeyboardLayout::addComputerKey(const ComputerKey computerKey)
{
    mComputerKeys.emplace_back(std::move(computerKey));
}


void KeyboardLayout::removeComputerKey(const ComputerKey & computerKey)
{
    auto foundComputerKey =
        std::find(mComputerKeys.begin(), mComputerKeys.end(), computerKey);

    if (foundComputerKey != mComputerKeys.end())
    {
        mComputerKeys.erase(foundComputerKey);
    }
}


const std::vector<ComputerKey> & KeyboardLayout::computerKeys() const
{
    return mComputerKeys;
}

} // namespace KL
