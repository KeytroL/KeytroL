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

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <catch.hpp>
KL_RESTORE_WARNINGS


TEST_CASE("Query the count of MIDI out devices", "[MidiOut]")
{
    REQUIRE(KL::IO::MidiOut::deviceCount() == 42);
}


TEST_CASE("Query the name of the first MIDI out device", "[MidiOut]")
{
    REQUIRE(KL::IO::MidiOut::deviceName(0) == "Foo");
}


TEST_CASE("Play an A4 on the first MIDI out device", "[MidiOut]")
{
    KL::IO::MidiOut midiOut(0);

    midiOut.sendMessage(0x90, 69, 100);

    REQUIRE(KL::IO::TestMidiOut::instance().message().statusByte == 0x90);
    REQUIRE(KL::IO::TestMidiOut::instance().message().dataByte1 == 69);
    REQUIRE(KL::IO::TestMidiOut::instance().message().dataByte2 == 100);

    midiOut.sendMessage(0x80, 69, 64);

    REQUIRE(KL::IO::TestMidiOut::instance().message().statusByte == 0x80);
    REQUIRE(KL::IO::TestMidiOut::instance().message().dataByte1 == 69);
    REQUIRE(KL::IO::TestMidiOut::instance().message().dataByte2 == 64);
}
