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

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <QtGui/QGuiApplication>
#include <QtQml/qqml.h>
#include <QtQml/QQmlApplicationEngine>
KL_RESTORE_WARNINGS


int main(int argc, char * argv[])
{
    QGuiApplication application(argc, argv);

    qmlRegisterType<KL::ViewKeyboard>("KeytroL.Keyboard", 1, 0, "Keyboard");
    qmlRegisterType<KL::KeyboardLayoutViewModel>(
        "KeytroL.Keyboard", 1, 0, "KeyboardLayout");
    qmlRegisterType<KL::XmlKeyboardLayout>("KeytroL.Keyboard", 1, 0, "XmlKeyboardLayout");

    auto midiOutDevicesSingletonProvider = [](QQmlEngine *, QJSEngine *) -> QObject *
    {
        return new KL::ViewMidiOutDevices;
    };

    qmlRegisterSingletonType<KL::ViewMidiOutDevices>(
        "KeytroL.Midi", 1, 0, "MidiOutDevices", midiOutDevicesSingletonProvider);
    qmlRegisterType<KL::ViewMidiOut>("KeytroL.Midi", 1, 0, "MidiOut");

    QQmlApplicationEngine engine(QUrl::fromLocalFile(QML_MAIN));

    return application.exec();
}
