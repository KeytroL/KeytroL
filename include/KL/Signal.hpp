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

#include <functional>
#include <vector>


namespace KL
{

template <typename T>
class Signal
{
public:
    Signal();

    Signal(const Signal &) = delete;
    Signal & operator=(const Signal &) = delete;

    void connect(std::function<void(T)> slot);

protected:
    std::vector<std::function<void(T)>> mSlots;
};


template <typename T>
class PrivateSignal : public Signal<T>
{
public:
    void emit(T value) const;
};

} // namespace KL


#include "detail/Signal.ipp"