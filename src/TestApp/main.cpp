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

#include "KL/Core/Warnings.hpp"
#include "KL/Keyboard/Keyboard.hpp"
#include "KL/Keyboard/KeyboardLayout.hpp"
#include "KL/Midi/MidiOut.hpp"

KL_DISABLE_WARNINGS
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
KL_RESTORE_WARNINGS


int main(int argc, char * argv[])
{
    QApplication application(argc, argv);

    QMainWindow window;
    window.show();

    KL::KeyboardLayout keyboardLayout;
    const auto computerKey = keyboardLayout.addComputerKey(0, 0, 2, 2);

    KL::Keyboard keyboard;
    const KL::MidiOut midiOut(0);

    keyboard.keyPressed().connect(
        [&computerKey, &midiOut](const KL::Keyboard::KeyCode keyCode)
        {
            (*computerKey)->keyCode().setValue(keyCode);
            qDebug() << "pressed : " << (*computerKey)->keyCode().value();

            const auto note = keyCode % 0x80;
            midiOut.sendMessage(0x90, static_cast<KL::MidiOut::Byte>(note), 100);
        });

    keyboard.keyReleased().connect(
        [&computerKey, &midiOut](const KL::Keyboard::KeyCode keyCode)
        {
            (*computerKey)->keyCode().setValue(keyCode);
            qDebug() << "released: " << (*computerKey)->keyCode().value();

            const auto note = keyCode % 0x80;
            midiOut.sendMessage(0x80, static_cast<KL::MidiOut::Byte>(note), 0);
        });

    qDebug() << KL::MidiOut::deviceCount() << "MIDI out device(s)";
    qDebug() << "First device:" << QString::fromStdString(KL::MidiOut::deviceName(0));
    qDebug() << "Second device:" << QString::fromStdString(KL::MidiOut::deviceName(1));
    qDebug() << "Third device:" << QString::fromStdString(KL::MidiOut::deviceName(2));

    return application.exec();
}
