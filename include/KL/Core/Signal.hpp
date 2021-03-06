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

#include "KL/Core/Connection.hpp"

#include <functional>
#include <memory>
#include <utility>
#include <vector>


namespace KL
{
namespace Core
{

template <typename T>
class Signal
{
public:
    Signal() = default;

    Signal(const Signal &) = delete;
    Signal & operator=(const Signal &) = delete;

    Signal(Signal && other);
    Signal & operator=(Signal && other);

    Connection connect(std::function<void(T)> slot);

protected:
    std::vector<std::pair<std::shared_ptr<bool>, std::function<void(T)>>> mSlots;
};


template <typename T>
class PrivateSignal : public Signal<T>
{
public:
    PrivateSignal() = default;

    PrivateSignal(PrivateSignal && other);
    PrivateSignal & operator=(PrivateSignal && other);

    void emit(const T & value) const;
};

} // namespace Core
} // namespace KL


#include "detail/Signal.ipp"
