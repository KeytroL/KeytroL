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

#include "KL/Core/Warnings.hpp"

KL_DISABLE_WARNINGS
#include <QtCore/QObject>
KL_RESTORE_WARNINGS


namespace KL
{

class ViewMidiOutDevices : public QObject
{
    Q_OBJECT

public:
    ViewMidiOutDevices(QObject * parent = nullptr);

    Q_INVOKABLE unsigned int count() const;
    Q_INVOKABLE QString name(unsigned int index) const;
};

} // namespace KL
