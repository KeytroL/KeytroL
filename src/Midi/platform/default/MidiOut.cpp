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

#include "KL/Midi/MidiOut.hpp"


namespace KL
{

class MidiOut::PlatformImpl
{
};


unsigned int MidiOut::deviceCount()
{
    return 0;
}


std::string MidiOut::deviceName(const unsigned int)
{
    return {};
}


MidiOut::MidiOut(const unsigned int)
    : mPlatformImpl(nullptr)
{
}


MidiOut::~MidiOut() = default;


void MidiOut::sendMessage(const Byte, const Byte, const Byte) const
{
}

} // namespace KL