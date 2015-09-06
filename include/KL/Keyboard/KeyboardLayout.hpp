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

#include "KL/Keyboard/ComputerKey.hpp"

#include <memory>
#include <set>


namespace KL
{

class KeyboardLayout
{
    using ComputerKeySet = std::set<std::unique_ptr<KL::ComputerKey>>;
    using ComputerKeyIterator = ComputerKeySet::const_iterator;

public:
    KeyboardLayout();

    ComputerKeyIterator addComputerKey(
        int x, int y, unsigned int width, unsigned int height);
    void removeComputerKey(ComputerKeyIterator computerKeyIt);

    const ComputerKeySet & computerKeys() const;

private:
    ComputerKeySet mComputerKeys;
};

} // namespace KL
