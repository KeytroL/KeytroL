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

#include "KL/MidiOut.hpp"

#include "KL/Warnings.hpp"

KL_DISABLE_WARNINGS
#include <Windows.h>
#include <Mmsystem.h>
KL_RESTORE_WARNINGS


namespace KL
{

class MidiOut::PlatformImpl
{
public:
    HMIDIOUT mMidiOutHandle;

    union MidiMessage
    {
        BYTE bytes[4];
        DWORD doubleWord;
    };
};


unsigned int MidiOut::deviceCount()
{
    return midiOutGetNumDevs();
}


std::string MidiOut::deviceName(unsigned int deviceIndex)
{
    MIDIOUTCAPS midiOutCaps;
    if (MMSYSERR_NOERROR
        == midiOutGetDevCaps(deviceIndex, &midiOutCaps, sizeof(midiOutCaps)))
    {
        return {midiOutCaps.szPname};
    }
    return {};
}


MidiOut::MidiOut(unsigned int deviceIndex)
    : mPlatformImpl(std::unique_ptr<PlatformImpl>(new PlatformImpl))
{
    midiOutOpen(&mPlatformImpl->mMidiOutHandle, deviceIndex, 0, 0, CALLBACK_NULL);
}


MidiOut::~MidiOut()
{
    midiOutReset(mPlatformImpl->mMidiOutHandle);
    midiOutClose(mPlatformImpl->mMidiOutHandle);
}


void MidiOut::sendMessage(Byte statusByte, Byte dataByte1, Byte dataByte2) const
{
    PlatformImpl::MidiMessage message = {statusByte, dataByte1, dataByte2, 0};

    midiOutShortMsg(mPlatformImpl->mMidiOutHandle, message.doubleWord);
}

} // namespace KL
