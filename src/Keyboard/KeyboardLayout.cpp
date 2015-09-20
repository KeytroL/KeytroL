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

#include <iterator>


namespace KL
{

KeyboardLayout::KeyboardLayout(KeyboardLayout && other)
    : mComputerKeys(std::move(other.mComputerKeys))
    , mComputerKeyAboutToBeAdded(std::move(other.mComputerKeyAboutToBeAdded))
    , mComputerKeyAdded(std::move(other.mComputerKeyAdded))
    , mComputerKeyAboutToBeRemoved(std::move(other.mComputerKeyAboutToBeRemoved))
    , mComputerKeyRemoved(std::move(other.mComputerKeyRemoved))
{
}


KeyboardLayout & KeyboardLayout::operator=(KeyboardLayout && other)
{
    mComputerKeys = std::move(other.mComputerKeys);
    mComputerKeyAboutToBeAdded = std::move(other.mComputerKeyAboutToBeAdded);
    mComputerKeyAdded = std::move(other.mComputerKeyAdded);
    mComputerKeyAboutToBeRemoved = std::move(other.mComputerKeyAboutToBeRemoved);
    mComputerKeyRemoved = std::move(other.mComputerKeyRemoved);
    return *this;
}


void KeyboardLayout::addComputerKey(ComputerKey computerKey)
{
    auto index = mComputerKeys.size();
    mComputerKeyAboutToBeAdded.emit(index);
    mComputerKeys.emplace_back(std::move(computerKey));
    mComputerKeyAdded.emit(index);
}


Signal<KeyboardLayout::SizeType> & KeyboardLayout::computerKeyAboutToBeAdded()
{
    return mComputerKeyAboutToBeAdded;
}


Signal<KeyboardLayout::SizeType> & KeyboardLayout::computerKeyAdded()
{
    return mComputerKeyAdded;
}


void KeyboardLayout::removeComputerKey(const SizeType index)
{
    if (index < mComputerKeys.size())
    {
        mComputerKeyAboutToBeRemoved.emit(index);
        auto it = mComputerKeys.begin();
        std::advance(it, static_cast<std::vector<ComputerKey>::difference_type>(index));
        mComputerKeys.erase(it);
        mComputerKeyRemoved.emit(index);
    }
}


Signal<KeyboardLayout::SizeType> & KeyboardLayout::computerKeyAboutToBeRemoved()
{
    return mComputerKeyAboutToBeRemoved;
}


Signal<KeyboardLayout::SizeType> & KeyboardLayout::computerKeyRemoved()
{
    return mComputerKeyRemoved;
}


const std::vector<ComputerKey> & KeyboardLayout::computerKeys() const
{
    return mComputerKeys;
}

} // namespace KL
