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

#include <vector>


namespace KL
{

template <typename T>
class NotifyingVector
{
public:
    using SizeType = typename std::vector<T>::size_type;
    using Vector = typename std::vector<T>;

    NotifyingVector() = default;

    NotifyingVector(Vector && vector);

    const Vector & vector() const;

    void replace(SizeType first, SizeType last, const Vector & replacement);

private:
    Vector mVector;
};

} // namespace KL


#include "detail/NotifyingVector.ipp"
