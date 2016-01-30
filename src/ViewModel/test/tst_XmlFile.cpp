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

#include "KL/ViewModel/XmlFile.hpp"

#include "KL/ViewModel/KeyboardLayout.hpp"

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <catch.hpp>
KL_RESTORE_WARNINGS


TEST_CASE("Cannot load without a valid KeyboardLayout", "[XmlFile]")
{
    KL::ViewModel::XmlFile xmlFile;

    REQUIRE_FALSE(xmlFile.load(QUrl{"file:test-layout.xml"}, nullptr));
}


TEST_CASE("Cannot load from a non-existing file", "[XmlFile]")
{
    KL::ViewModel::XmlFile xmlFile;
    KL::ViewModel::KeyboardLayout keyboardLayout;

    REQUIRE_FALSE(xmlFile.load(QUrl{"file:do-not-exist.xml"}, &keyboardLayout));
}


TEST_CASE("Cannot save without a valid KeyboardLayout", "[XmlFile]")
{
    KL::ViewModel::XmlFile xmlFile;

    REQUIRE_FALSE(xmlFile.save(QUrl{"file:test-layout.xml"}, nullptr));
}


TEST_CASE("Cannot save to an invalid file path", "[XmlFile]")
{
    KL::ViewModel::XmlFile xmlFile;
    KL::ViewModel::KeyboardLayout keyboardLayout;

    REQUIRE_FALSE(xmlFile.save(QUrl{"invalid.xml"}, &keyboardLayout));
}


TEST_CASE("Loading a saved keyboard layout creates the same keyboard layout", "[XmlFile]")
{
    KL::ViewModel::XmlFile xmlFile;

    KL::ViewModel::KeyboardLayout saved;
    saved.addComputerKey(0, 0, 4, 4, "Esc", 1);
    saved.addComputerKey(15, 22, 25, 4, "", 57);
    saved.addComputerKey(88, 10, 4, 8, "+", 78);

    REQUIRE(xmlFile.save(QUrl{"file:test-layout.xml"}, &saved));

    KL::ViewModel::KeyboardLayout loaded;

    REQUIRE(xmlFile.load(QUrl{"file:test-layout.xml"}, &loaded));

    REQUIRE(loaded.model().computerKeys() == saved.model().computerKeys());
}
