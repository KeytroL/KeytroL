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

#include "KeyboardPlatformImpl.hpp"


namespace KL
{

Keyboard::PlatformImpl & Keyboard::PlatformImpl::instance()
{
    static PlatformImpl platformKeyboard;
    return platformKeyboard;
}


void Keyboard::PlatformImpl::addKeyboard(const Keyboard * keyboard)
{
    mKeyboards.insert(keyboard);
}


void Keyboard::PlatformImpl::removeKeyboard(const Keyboard * keyboard)
{
    mKeyboards.erase(keyboard);
}


Keyboard::PlatformImpl::PlatformImpl()
{
    const auto lowLevelKeyboardProc = [](int nCode, WPARAM wParam, LPARAM lParam)
                                          -> LRESULT
    {
        if (nCode == HC_ACTION)
        {
            const auto & platformKeyboard = PlatformImpl::instance();
            const auto hookStruct = reinterpret_cast<const KBDLLHOOKSTRUCT *>(lParam);

            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
            {
                platformKeyboard.pressKey(hookStruct->scanCode);
            }
            else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
            {
                platformKeyboard.releaseKey(hookStruct->scanCode);
            }
        }

        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    };

    mLowLevelKeyboardHookHandle = SetWindowsHookEx(
        WH_KEYBOARD_LL, lowLevelKeyboardProc, GetModuleHandle(nullptr), 0);
}


Keyboard::PlatformImpl::~PlatformImpl()
{
    UnhookWindowsHookEx(mLowLevelKeyboardHookHandle);
}


void Keyboard::PlatformImpl::pressKey(Keyboard::KeyCode keyCode) const
{
    for (const auto * keyboard : mKeyboards)
    {
        keyboard->pressKey(keyCode);
    }
}


void Keyboard::PlatformImpl::releaseKey(Keyboard::KeyCode keyCode) const
{
    for (const auto * keyboard : mKeyboards)
    {
        keyboard->releaseKey(keyCode);
    }
}

} // namespace KL
