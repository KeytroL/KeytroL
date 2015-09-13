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

#include "KL/Core/Warnings.hpp"
#include "KL/Keyboard/ComputerKey.hpp"
#include "KL/Keyboard/Keyboard.hpp"
#include "KL/Keyboard/KeyboardLayout.hpp"
#include "KL/Keyboard/KeyMapping.hpp"
#include "KL/Midi/MidiOut.hpp"

KL_DISABLE_WARNINGS
#include <QtCore/QDebug>
#include <QtQml/qqml.h>
#include <QtQml/QQmlContext>
#include <QtQuickWidgets/QQuickWidget>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
KL_RESTORE_WARNINGS


int main(int argc, char * argv[])
{
    const KL::MidiOut midiOut(0);

    qDebug() << KL::MidiOut::deviceCount() << "MIDI out device(s)";
    qDebug() << "First device:" << QString::fromStdString(KL::MidiOut::deviceName(0));
    qDebug() << "Second device:" << QString::fromStdString(KL::MidiOut::deviceName(1));
    qDebug() << "Third device:" << QString::fromStdString(KL::MidiOut::deviceName(2));


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

    keyboard.keyPressed().connect([&keyMapping](const KL::Keyboard::KeyCode keyCode)
        {
            qDebug() << "pressed : " << keyCode;
            keyMapping.at(keyCode, KL::Keyboard::KeyState::Pressed)();
        });

    keyboard.keyReleased().connect([&keyMapping](const KL::Keyboard::KeyCode keyCode)
        {
            qDebug() << "released: " << keyCode;
            keyMapping.at(keyCode, KL::Keyboard::KeyState::Released)();
        });


    KL::KeyboardLayout keyboardLayout;
    unsigned char offset = 0;

    const auto addComputerKey = [&keyboardLayout, &offset]()
    {
        KL::ComputerKey computerKey{
            4 * offset, offset, 4, 4, std::string(1, 'A' + offset), 1u + offset};
        keyboardLayout.addComputerKey(computerKey);
        ++offset;
    };

    addComputerKey();
    addComputerKey();
    addComputerKey();

    KL::KeyboardLayoutViewModel viewModel(keyboardLayout);


    QApplication application(argc, argv);

    qmlRegisterType<KL::ViewKeyboard>("KL.Keyboard", 1, 0, "Keyboard");

    auto quickWidget = new QQuickWidget;
    quickWidget->rootContext()->setContextProperty("theKeyboardLayout", &viewModel);
    quickWidget->setSource(QUrl::fromLocalFile(QML_MAIN));

    QMainWindow window;
    window.setCentralWidget(quickWidget);

    QObject::connect(
        window.menuBar()->addAction("Add"), &QAction::triggered, addComputerKey);
    QObject::connect(window.menuBar()->addAction("Remove"),
        &QAction::triggered,
        [&keyboardLayout]()
        {
            if (!keyboardLayout.computerKeys().empty())
            {
                const auto index = keyboardLayout.computerKeys().size() / 2;
                keyboardLayout.removeComputerKey(keyboardLayout.computerKeys().at(index));
            }
        });

    window.show();

    return application.exec();
}
