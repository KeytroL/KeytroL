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

#include "KL/ViewIO/ViewKeyboardInput.hpp"
#include "KL/ViewIO/ViewMidiOut.hpp"
#include "KL/ViewIO/ViewMidiOutDevices.hpp"
#include "KL/ViewModel/KeyboardLayoutViewModel.hpp"
#include "KL/ViewModel/XmlKeyboardLayout.hpp"

#include "KL/Warnings.hpp"
KL_DISABLE_WARNINGS
#include <QtGui/QGuiApplication>
#include <QtQml/qqml.h>
#include <QtQml/QQmlApplicationEngine>
KL_RESTORE_WARNINGS


int main(int argc, char * argv[])
{
    QGuiApplication application(argc, argv);

    auto midiOutDevicesSingletonProvider = [](QQmlEngine *, QJSEngine *) -> QObject *
    {
        return new KL::ViewIO::ViewMidiOutDevices;
    };

    qmlRegisterSingletonType<KL::ViewIO::ViewMidiOutDevices>(
        "KeytroL.IO", 1, 0, "MidiOutDevices", midiOutDevicesSingletonProvider);

    qmlRegisterType<KL::ViewIO::ViewKeyboardInput>("KeytroL.IO", 1, 0, "KeyboardInput");
    qmlRegisterType<KL::ViewIO::ViewMidiOut>("KeytroL.IO", 1, 0, "MidiOut");

    qmlRegisterType<KL::KeyboardLayoutViewModel>("KeytroL.Model", 1, 0, "KeyboardLayout");
    qmlRegisterType<KL::XmlKeyboardLayout>("KeytroL.Model", 1, 0, "XmlKeyboardLayout");

    QQmlApplicationEngine engine(QUrl::fromLocalFile(QML_MAIN));

    return application.exec();
}
