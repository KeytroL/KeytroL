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

#include "KL/ViewIO/MidiOut.hpp"

#include "KL/IO/MidiOut.hpp"


namespace KL
{
namespace ViewIO
{

MidiOut::MidiOut(QObject * parent)
    : QObject(parent)
    , mDeviceIndex(-1)
    , mDevice(nullptr)
{
    QObject::connect(this, &MidiOut::deviceIndexChanged, this, &MidiOut::updateDevice);
}


MidiOut::~MidiOut() = default;


void MidiOut::sendMessage(
    unsigned char statusByte, unsigned char dataByte1, unsigned char dataByte2) const
{
    if (mDevice)
    {
        mDevice->sendMessage(statusByte, dataByte1, dataByte2);
    }
}


int MidiOut::deviceIndex() const
{
    return mDeviceIndex;
}


void MidiOut::setDeviceIndex(int deviceIndex)
{
    if (mDeviceIndex != deviceIndex)
    {
        mDeviceIndex = deviceIndex;
        Q_EMIT deviceIndexChanged();
    }
}


void MidiOut::updateDevice()
{
    if (mDeviceIndex >= 0
        && static_cast<unsigned int>(mDeviceIndex) < IO::MidiOut::deviceCount())
    {
        mDevice.reset(new IO::MidiOut{static_cast<unsigned int>(mDeviceIndex)});
    }
    else
    {
        mDevice.reset();
    }
}

} // namespace ViewIO
} // namespace KL
