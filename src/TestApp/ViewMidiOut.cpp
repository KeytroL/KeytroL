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

#include "ViewMidiOut.hpp"

#include "KL/Midi/MidiOut.hpp"


namespace KL
{

ViewMidiOut::ViewMidiOut(QObject * parent)
    : QObject(parent)
    , mDeviceIndex(-1)
    , mDevice(nullptr)
{
    QObject::connect(
        this, &ViewMidiOut::deviceIndexChanged, this, &ViewMidiOut::updateDevice);
}


ViewMidiOut::~ViewMidiOut() = default;


void ViewMidiOut::sendMessage(
    unsigned char statusByte, unsigned char dataByte1, unsigned char dataByte2) const
{
    if (mDevice)
    {
        mDevice->sendMessage(statusByte, dataByte1, dataByte2);
    }
}


int ViewMidiOut::deviceIndex() const
{
    return mDeviceIndex;
}


void ViewMidiOut::setDeviceIndex(int deviceIndex)
{
    if (mDeviceIndex != deviceIndex)
    {
        mDeviceIndex = deviceIndex;
        Q_EMIT deviceIndexChanged();
    }
}


void ViewMidiOut::updateDevice()
{
    if (mDeviceIndex >= 0)
    {
        mDevice.reset(new MidiOut(static_cast<unsigned int>(mDeviceIndex)));
    }
}

} // namespace KL
