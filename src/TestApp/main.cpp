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

#include "KL/ViewIO/KeyboardInput.hpp"
#include "KL/ViewIO/MidiOut.hpp"
#include "KL/ViewIO/MidiOutDevices.hpp"
#include "KL/ViewModel/KeyboardLayout.hpp"
#include "KL/ViewModel/XmlFile.hpp"

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
        return new KL::ViewIO::MidiOutDevices;
    };

    qmlRegisterSingletonType<KL::ViewIO::MidiOutDevices>(
        "KeytroL.IO", 1, 0, "MidiOutDevices", midiOutDevicesSingletonProvider);

    qmlRegisterType<KL::ViewIO::KeyboardInput>("KeytroL.IO", 1, 0, "KeyboardInput");
    qmlRegisterType<KL::ViewIO::MidiOut>("KeytroL.IO", 1, 0, "MidiOut");

    qmlRegisterType<KL::ViewModel::KeyboardLayout>(
        "KeytroL.Model", 1, 0, "KeyboardLayout");
    qmlRegisterType<KL::ViewModel::XmlFile>("KeytroL.Model", 1, 0, "XmlFile");

    QQmlApplicationEngine engine(QUrl("qrc:main.qml"));

    return application.exec();
}
