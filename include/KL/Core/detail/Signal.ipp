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


namespace KL
{
namespace Core
{

template <typename T>
Signal<T>::Signal(Signal && other)
    : mSlots(std::move(other.mSlots))
{
}


template <typename T>
Signal<T> & Signal<T>::operator=(Signal && other)
{
    mSlots = std::move(other.mSlots);
    return *this;
}


template <typename T>
Connection Signal<T>::connect(std::function<void(T)> slot)
{
    mSlots.emplace_back(std::make_shared<bool>(true), std::move(slot));
    return Connection{mSlots.back().first};
}


template <typename T>
PrivateSignal<T>::PrivateSignal(PrivateSignal && other)
    : Signal<T>(std::move(other))
{
}


template <typename T>
PrivateSignal<T> & PrivateSignal<T>::operator=(PrivateSignal && other)
{
    Signal<T>::operator=(std::move(other));
    return *this;
}


template <typename T>
void PrivateSignal<T>::emit(const T & value) const
{
    for (const auto & slot : PrivateSignal<T>::mSlots)
    {
        if (*slot.first == true)
        {
            slot.second(value);
        }
    }
}

} // namespace Core
} // namespace KL
