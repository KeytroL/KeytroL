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

#include "KL/Core/Signal.hpp"


namespace KL
{
namespace Core
{

template <typename T>
class Property
{
public:
    explicit Property(T value);

    const T & value() const;
    void setValue(const T & value);
    Signal<T> & valueChanged();

private:
    T mValue;
    PrivateSignal<T> mValueChanged;
};

} // namespace Core
} // namespace KL


#include "detail/Property.ipp"
