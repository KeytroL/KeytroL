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

#include "TestMidiOut.hpp"


namespace KL
{
namespace IO
{

TestMidiOut & TestMidiOut::instance()
{
    static TestMidiOut testMidiOut;
    return testMidiOut;
}


unsigned int TestMidiOut::deviceCount()
{
    return 42;
}


std::string TestMidiOut::deviceName(unsigned int)
{
    return {"Foo"};
}


const TestMidiOut::Message & TestMidiOut::message() const
{
    return mMessage;
}

} // namespace IO
} // namespace KL
