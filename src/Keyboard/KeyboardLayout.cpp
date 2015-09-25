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
    auto index = mComputerKeys.vector().size();
    mComputerKeyAboutToBeAdded.emit(index);
    mComputerKeys.replace(index, index, {std::move(computerKey)});
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


void KeyboardLayout::removeComputerKey(SizeType index)
{
    if (index < mComputerKeys.vector().size())
    {
        mComputerKeyAboutToBeRemoved.emit(index);
        mComputerKeys.replace(index, index + 1, {});
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


const NotifyingVector<ComputerKey>::Vector & KeyboardLayout::computerKeys() const
{
    return mComputerKeys.vector();
}


Signal<const NotifyingVector<ComputerKey>::Notification &> &
KeyboardLayout::beforeReplace()
{
    return mComputerKeys.beforeReplace();
}


Signal<const NotifyingVector<ComputerKey>::Notification &> &
KeyboardLayout::afterReplace()
{
    return mComputerKeys.afterReplace();
}

} // namespace KL
