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

#include "ViewKeyboard.hpp"


namespace KL
{

ViewKeyboard::ViewKeyboard(QObject * parent)
    : QObject(parent)
{
    mKeyboard.keyPressed().connect([this](Keyboard::KeyCode keyCode)
        {
            Q_EMIT keyPressed(keyCode);
        });

    mKeyboard.keyReleased().connect([this](Keyboard::KeyCode keyCode)
        {
            Q_EMIT keyReleased(keyCode);
        });
}

} // namespace KL
