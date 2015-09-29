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

#include <utility>


namespace KL
{
namespace Core
{

template <typename T>
Property<T>::Property(T value)
    : mValue(std::move(value))
{
}


template <typename T>
const T & Property<T>::value() const
{
    return mValue;
}


template <typename T>
void Property<T>::setValue(const T & value)
{
    if (mValue != value)
    {
        mValue = value;
        mValueChanged.emit(mValue);
    }
}


template <typename T>
Signal<T> & Property<T>::valueChanged()
{
    return mValueChanged;
}

} // namespace Core
} // namespace KL
