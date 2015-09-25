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

#include <stdexcept>


namespace KL
{

template <typename T>
NotifyingVector<T>::NotifyingVector(Vector && vector)
    : mVector(std::move(vector))
{
}


template <typename T>
const typename NotifyingVector<T>::Vector & NotifyingVector<T>::vector() const
{
    return mVector;
}


template <typename T>
void NotifyingVector<T>::replace(
    SizeType first, SizeType last, const Vector & replacement)
{
    if (first > last || last > mVector.size())
    {
        throw std::invalid_argument("invalid argument: first or last");
    }

    if (first != last)
    {
        mVector.erase(
            mVector.begin() + static_cast<typename Vector::difference_type>(first),
            mVector.begin() + static_cast<typename Vector::difference_type>(last));
    }

    if (replacement.size() > 0)
    {
        mVector.insert(
            mVector.begin() + static_cast<typename Vector::difference_type>(first),
            replacement.begin(),
            replacement.end());
    }
}

} // namespace KL
