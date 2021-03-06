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

#include "KL/IO/MidiOut.hpp"

#include "TestMidiOut.hpp"


namespace KL
{
namespace IO
{

class MidiOut::PlatformImpl
{
};


unsigned int MidiOut::deviceCount()
{
    return TestMidiOut::deviceCount();
}


std::string MidiOut::deviceName(unsigned int deviceIndex)
{
    return TestMidiOut::deviceName(deviceIndex);
}


MidiOut::MidiOut(unsigned int)
    : mPlatformImpl(nullptr)
{
}


MidiOut::~MidiOut() = default;


void MidiOut::sendMessage(Byte statusByte, Byte dataByte1, Byte dataByte2) const
{
    TestMidiOut::instance().mMessage = {statusByte, dataByte1, dataByte2};
}

} // namespace IO
} // namespace KL
