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

#include "TestMidiOut.hpp"

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <catch.hpp>
#include <QtCore/QVariant>
#include <QtTest/QSignalSpy>
KL_RESTORE_WARNINGS


TEST_CASE("The default device index is not a valid device index", "[MidiOut]")
{
    KL::ViewIO::MidiOut midiOut;

    REQUIRE(midiOut.deviceIndex() == -1);
}


TEST_CASE("Setting a new device index emits a signal", "[MidiOut]")
{
    KL::ViewIO::MidiOut midiOut;
    QSignalSpy deviceIndexChangedSpy(&midiOut, SIGNAL(deviceIndexChanged()));

    midiOut.setDeviceIndex(23);

    REQUIRE(midiOut.deviceIndex() == 23);
    REQUIRE(deviceIndexChangedSpy.count() == 1);

    midiOut.setDeviceIndex(23);

    REQUIRE(midiOut.deviceIndex() == 23);
    REQUIRE(deviceIndexChangedSpy.count() == 1);
}


TEST_CASE(
    "Sending a MIDI message only works when there is an underlying device", "[MidiOut]")
{
    KL::ViewIO::MidiOut midiOut;

    midiOut.setDeviceIndex(23);
    midiOut.sendMessage(0x80, 69, 100);

    REQUIRE(KL::IO::TestMidiOut::instance().message().statusByte == 0x80);
    REQUIRE(KL::IO::TestMidiOut::instance().message().dataByte1 == 69);
    REQUIRE(KL::IO::TestMidiOut::instance().message().dataByte2 == 100);

    midiOut.setDeviceIndex(-1);
    midiOut.sendMessage(0x90, 42, 64);

    REQUIRE(KL::IO::TestMidiOut::instance().message().statusByte == 0x80);
    REQUIRE(KL::IO::TestMidiOut::instance().message().dataByte1 == 69);
    REQUIRE(KL::IO::TestMidiOut::instance().message().dataByte2 == 100);

    REQUIRE_FALSE(77 < KL::IO::MidiOut::deviceCount());
    midiOut.setDeviceIndex(77);
    midiOut.sendMessage(0x90, 42, 64);

    REQUIRE(KL::IO::TestMidiOut::instance().message().statusByte == 0x80);
    REQUIRE(KL::IO::TestMidiOut::instance().message().dataByte1 == 69);
    REQUIRE(KL::IO::TestMidiOut::instance().message().dataByte2 == 100);
}
