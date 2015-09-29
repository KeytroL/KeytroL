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

#include "KeyboardInputPlatformImpl.hpp"


namespace KL
{
namespace IO
{

KeyboardInput::PlatformImpl & KeyboardInput::PlatformImpl::instance()
{
    static PlatformImpl platformKeyboard;
    return platformKeyboard;
}


void KeyboardInput::PlatformImpl::addKeyboardInput(const KeyboardInput * keyboardInput)
{
    mKeyboardInputs.insert(keyboardInput);
}


void KeyboardInput::PlatformImpl::removeKeyboardInput(const KeyboardInput * keyboardInput)
{
    mKeyboardInputs.erase(keyboardInput);
}


KeyboardInput::PlatformImpl::PlatformImpl()
{
    const auto lowLevelKeyboardProc = [](int nCode, WPARAM wParam, LPARAM lParam)
                                          -> LRESULT
    {
        if (nCode == HC_ACTION)
        {
            const auto & platformKeyboardInput = PlatformImpl::instance();
            const auto hookStruct = reinterpret_cast<const KBDLLHOOKSTRUCT *>(lParam);

            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
            {
                platformKeyboardInput.pressKey(hookStruct->scanCode);
            }
            else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
            {
                platformKeyboardInput.releaseKey(hookStruct->scanCode);
            }
        }

        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    };

    mLowLevelKeyboardHookHandle = SetWindowsHookEx(
        WH_KEYBOARD_LL, lowLevelKeyboardProc, GetModuleHandle(nullptr), 0);
}


KeyboardInput::PlatformImpl::~PlatformImpl()
{
    UnhookWindowsHookEx(mLowLevelKeyboardHookHandle);
}


void KeyboardInput::PlatformImpl::pressKey(KeyCode keyCode) const
{
    for (const auto * keyboardInput : mKeyboardInputs)
    {
        keyboardInput->pressKey(keyCode);
    }
}


void KeyboardInput::PlatformImpl::releaseKey(KeyCode keyCode) const
{
    for (const auto * keyboardInput : mKeyboardInputs)
    {
        keyboardInput->releaseKey(keyCode);
    }
}

} // namespace IO
} // namespace KL
