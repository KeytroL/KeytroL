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

#include "KL/ViewIO/MidiOutDevices.hpp"

#include "KL/IO/MidiOut.hpp"

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <catch.hpp>
KL_RESTORE_WARNINGS


TEST_CASE("MidiOutDevices replicates the static interface of IO::MidiOut",
          "[MidiOutDevices]")
{
    KL::ViewIO::MidiOutDevices devices;

    REQUIRE(devices.count() == KL::IO::MidiOut::deviceCount());
    REQUIRE(devices.name(0).toStdString() == KL::IO::MidiOut::deviceName(0));
}
