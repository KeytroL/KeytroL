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

#include "KL/Model/KeyboardLayout.hpp"

#include <iterator>


namespace KL
{
namespace Model
{

KeyboardLayout::KeyboardLayout(KeyboardLayout && other)
    : mComputerKeys(std::move(other.mComputerKeys))
{
}


KeyboardLayout & KeyboardLayout::operator=(KeyboardLayout && other)
{
    mComputerKeys = std::move(other.mComputerKeys);
    return *this;
}


void KeyboardLayout::addComputerKey(ComputerKey computerKey)
{
    auto index = mComputerKeys.vector().size();
    mComputerKeys.replace(index, index, {std::move(computerKey)});
}


void KeyboardLayout::removeComputerKey(SizeType index)
{
    if (index < mComputerKeys.vector().size())
    {
        mComputerKeys.replace(index, index + 1, {});
    }
}


const Core::NotifyingVector<ComputerKey>::Vector & KeyboardLayout::computerKeys() const
{
    return mComputerKeys.vector();
}


void KeyboardLayout::replace(
    SizeType first,
    SizeType last,
    const Core::NotifyingVector<ComputerKey>::Vector & replacement)
{
    mComputerKeys.replace(first, last, replacement);
}


Core::NotifyingVector<ComputerKey>::Notification & KeyboardLayout::beforeReplace()
{
    return mComputerKeys.beforeReplace();
}


Core::NotifyingVector<ComputerKey>::Notification & KeyboardLayout::afterReplace()
{
    return mComputerKeys.afterReplace();
}

} // namespace Model
} // namespace KL
