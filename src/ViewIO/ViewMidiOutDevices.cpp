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

#include "KL/ViewIO/ViewMidiOutDevices.hpp"

#include "KL/IO/MidiOut.hpp"


namespace KL
{

ViewMidiOutDevices::ViewMidiOutDevices(QObject * parent)
    : QObject(parent)
{
}


unsigned int ViewMidiOutDevices::count() const
{
    return MidiOut::deviceCount();
}


QString ViewMidiOutDevices::name(unsigned int index) const
{
    return QString::fromStdString(MidiOut::deviceName(index));
}

} // namespace KL
