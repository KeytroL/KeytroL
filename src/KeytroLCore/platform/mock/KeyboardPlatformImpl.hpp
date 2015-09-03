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

#include "KL/Keyboard.hpp"


namespace KL
{

class Keyboard::PlatformImpl
{
public:
    explicit PlatformImpl(const Keyboard & keyboard);

    void pressKey(Keyboard::KeyCode keyCode) const;
    void releaseKey(Keyboard::KeyCode keyCode) const;

private:
    const Keyboard & mKeyboard;
};

} // namespace KL
