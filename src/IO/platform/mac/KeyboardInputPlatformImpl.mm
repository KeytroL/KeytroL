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

#include <AppKit/AppKit.h>


namespace KL
{

KeyboardInput::PlatformImpl::PlatformImpl(const KeyboardInput & keyboardInput)
    : mKeyboardInput(keyboardInput)
{
    auto keyEventMonitorProc = [this](NSEvent * event) -> NSEvent *
    {
        auto type = [event type];
        auto keyCode = [event keyCode];

        if (type == NSKeyDown)
        {
            mKeyboardInput.pressKey(keyCode);
        }
        else if (type == NSKeyUp)
        {
            mKeyboardInput.releaseKey(keyCode);
        }

        return event;
    };

    mKeyEventMonitor = static_cast<void *>(
        [NSEvent addLocalMonitorForEventsMatchingMask:(NSKeyDownMask | NSKeyUpMask)
                                              handler:^(NSEvent * event) {
                                                return keyEventMonitorProc(event);
                                              }]);
}


KeyboardInput::PlatformImpl::~PlatformImpl()
{
    [NSEvent removeMonitor:static_cast<id>(mKeyEventMonitor)];
}

} // namespace KL
