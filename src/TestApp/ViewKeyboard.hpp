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

#include "KL/Keyboard/Keyboard.hpp"

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <QtCore/QObject>
KL_RESTORE_WARNINGS


namespace KL
{

class ViewKeyboard : public QObject
{
    Q_OBJECT

public:
    ViewKeyboard(QObject * parent = nullptr);

Q_SIGNALS:
    void keyPressed(int keyCode);
    void keyReleased(int keyCode);

private:
    Keyboard mKeyboard;
};

} // namespace KL
