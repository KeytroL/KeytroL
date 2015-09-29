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

#include "KL/Core/NotifyingVector.hpp"
#include "KL/Core/Signal.hpp"
#include "KL/Model/ComputerKey.hpp"


namespace KL
{

class KeyboardLayout
{
public:
    using SizeType = Core::NotifyingVector<ComputerKey>::SizeType;

    KeyboardLayout() = default;

    KeyboardLayout(KeyboardLayout && other);
    KeyboardLayout & operator=(KeyboardLayout && other);

    void addComputerKey(ComputerKey computerKey);
    void removeComputerKey(SizeType index);

    const Core::NotifyingVector<ComputerKey>::Vector & computerKeys() const;

    void replace(SizeType first,
        SizeType last,
        const Core::NotifyingVector<ComputerKey>::Vector & replacement);

    Core::NotifyingVector<ComputerKey>::Notification & beforeReplace();
    Core::NotifyingVector<ComputerKey>::Notification & afterReplace();

private:
    Core::NotifyingVector<ComputerKey> mComputerKeys;
};

} // namespace KL
