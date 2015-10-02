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


namespace KL
{
namespace IO
{

class TestMidiOut
{
public:
    static TestMidiOut & instance();

    static unsigned int deviceCount();
    static std::string deviceName(unsigned int deviceIndex);

    struct Message
    {
        MidiOut::Byte statusByte;
        MidiOut::Byte dataByte1;
        MidiOut::Byte dataByte2;
    };

    const Message & message() const;

private:
    TestMidiOut() = default;

    friend class KL::IO::MidiOut;

    Message mMessage;
};

} // namespace IO
} // namespace KL
