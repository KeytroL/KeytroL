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

#include "KeyboardLayoutViewModel.hpp"
#include "ViewKeyboard.hpp"
#include "ViewMidiOut.hpp"
#include "ViewMidiOutDevices.hpp"
#include "XmlKeyboardLayout.hpp"

#include "KL/Core/Warnings.hpp"
#include "KL/Keyboard/Keyboard.hpp"
#include "KL/Keyboard/KeyMapping.hpp"
#include "KL/Midi/MidiOut.hpp"

KL_DISABLE_WARNINGS
#include <QtGui/QGuiApplication>
#include <QtQml/qqml.h>
#include <QtQml/QQmlApplicationEngine>
KL_RESTORE_WARNINGS


int main(int argc, char * argv[])
{
    const KL::MidiOut midiOut(0);

    KL::KeyMapping keyMapping;

    for (KL::MidiOut::Byte note = 0; note < 0x80; ++note)
    {
        keyMapping.at(note, KL::Keyboard::KeyState::Pressed) = [&midiOut, note]()
        {
            midiOut.sendMessage(0x90, note, 100);
        };

        keyMapping.at(note, KL::Keyboard::KeyState::Released) = [&midiOut, note]()
        {
            midiOut.sendMessage(0x80, note, 0);
        };
    }


    KL::Keyboard keyboard;

    keyboard.keyPressed().connect([&keyMapping](KL::Keyboard::KeyCode keyCode)
        {
            keyMapping.at(keyCode, KL::Keyboard::KeyState::Pressed)();
        });

    keyboard.keyReleased().connect([&keyMapping](KL::Keyboard::KeyCode keyCode)
        {
            keyMapping.at(keyCode, KL::Keyboard::KeyState::Released)();
        });


    QGuiApplication application(argc, argv);

    qmlRegisterType<KL::ViewKeyboard>("KL.Keyboard", 1, 0, "Keyboard");
    qmlRegisterType<KL::KeyboardLayoutViewModel>("KL.Keyboard", 1, 0, "KeyboardLayout");
    qmlRegisterType<KL::XmlKeyboardLayout>("KL.Keyboard", 1, 0, "XmlKeyboardLayout");

    auto midiOutDevicesSingletonProvider = [](QQmlEngine *, QJSEngine *) -> QObject *
    {
        return new KL::ViewMidiOutDevices;
    };

    qmlRegisterSingletonType<KL::ViewMidiOutDevices>(
        "KL.Midi", 1, 0, "MidiOutDevices", midiOutDevicesSingletonProvider);
    qmlRegisterType<KL::ViewMidiOut>("KL.Midi", 1, 0, "MidiOut");

    QQmlApplicationEngine engine(QUrl::fromLocalFile(QML_MAIN));

    return application.exec();
}
