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
#include "KL/Keyboard/ComputerKey.hpp"

#include <vector>


namespace KL
{

class KeyboardLayout
{
public:
    using SizeType = std::vector<ComputerKey>::size_type;

    void addComputerKey(ComputerKey computerKey);
    Signal<SizeType> & computerKeyAboutToBeAdded();
    Signal<SizeType> & computerKeyAdded();

    void removeComputerKey(SizeType index);
    Signal<SizeType> & computerKeyAboutToBeRemoved();
    Signal<SizeType> & computerKeyRemoved();

    const std::vector<ComputerKey> & computerKeys() const;

private:
    std::vector<ComputerKey> mComputerKeys;

    PrivateSignal<SizeType> mComputerKeyAboutToBeAdded;
    PrivateSignal<SizeType> mComputerKeyAdded;
    PrivateSignal<SizeType> mComputerKeyAboutToBeRemoved;
    PrivateSignal<SizeType> mComputerKeyRemoved;
};

} // namespace KL
