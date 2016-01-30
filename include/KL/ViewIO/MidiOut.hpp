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

#pragma once

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <QtCore/QObject>
KL_RESTORE_WARNINGS

#include <memory>


namespace KL
{
namespace IO
{
class MidiOut;
}


namespace ViewIO
{

class MidiOut : public QObject
{
    Q_OBJECT

    Q_PROPERTY(
        int deviceIndex READ deviceIndex WRITE setDeviceIndex NOTIFY deviceIndexChanged)

Q_SIGNALS:
    void deviceIndexChanged();

public:
    MidiOut(QObject * parent = nullptr);
    ~MidiOut();

    Q_INVOKABLE void sendMessage(
        unsigned char statusByte, unsigned char dataByte1, unsigned char dataByte2) const;

    int deviceIndex() const;
    void setDeviceIndex(int deviceIndex);

private:
    void updateDevice();

    int mDeviceIndex;
    std::unique_ptr<IO::MidiOut> mDevice;
};

} // namespace ViewIO
} // namespace KL
