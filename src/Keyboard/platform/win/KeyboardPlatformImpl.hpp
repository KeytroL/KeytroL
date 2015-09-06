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

#include "KL/Core/Warnings.hpp"
#include "KL/Keyboard/Keyboard.hpp"

KL_DISABLE_WARNINGS
#include <Windows.h>
KL_RESTORE_WARNINGS

#include <set>


namespace KL
{

class Keyboard::PlatformImpl
{
public:
    static PlatformImpl & instance();
    ~PlatformImpl();

    void addKeyboard(const Keyboard * const keyboard);
    void removeKeyboard(const Keyboard * const keyboard);

private:
    PlatformImpl();

    void pressKey(Keyboard::KeyCode keyCode) const;
    void releaseKey(Keyboard::KeyCode keyCode) const;

    std::set<const Keyboard *> mKeyboards;

    HHOOK mLowLevelKeyboardHookHandle = nullptr;
};

} // namespace KL
