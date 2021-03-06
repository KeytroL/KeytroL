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

import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2

import KeytroL 1.0
import KeytroL.IO 1.0
import KeytroL.Model 1.0


ApplicationWindow {
    id: root

    visible: true
    width: 640
    height: 480

    readonly property int scale: 10
    readonly property int defaultKeySize: 4

    menuBar: MenuBar {
        Menu {
            title: "File"

            MenuItem {
                action: Action {
                    text: "Open..."

                    onTriggered: {
                        fileDialog.selectExisting = true;
                        fileDialog.open();
                    }
                }
            }

            MenuItem {
                action: Action {
                    id: saveAction

                    text: "Save"

                    onTriggered: {
                        if (fileDialog.fileUrl.toString() !== "") {
                            console.log("Saving file: " + fileDialog.fileUrl);
                            if (!xmlFile.save(fileDialog.fileUrl, keyboardLayout)) {
                                cannotSaveFileDialog.open();
                            }
                        }
                        else {
                            saveAsAction.trigger();
                        }
                    }
                }
            }

            MenuItem {
                action: Action {
                    id: saveAsAction

                    text: "Save As..."

                    onTriggered: {
                        fileDialog.selectExisting = false;
                        fileDialog.open();
                    }
                }
            }
        }

        Menu {
            id: midiOutMenu

            title: "MIDI Out"

            ExclusiveGroup {
                id: midiOutDevicesGroup
            }

            Instantiator {
                model: MidiOutDevices.count()

                delegate: MenuItem {
                    action: Action {
                        readonly property int deviceIndex: index

                        checkable: true
                        exclusiveGroup: midiOutDevicesGroup
                        text: MidiOutDevices.name(deviceIndex)
                    }
                }

                onObjectAdded: midiOutMenu.insertItem(index, object)
                onObjectRemoved: midiOutMenu.removeItem(object)
            }
        }
    }

    FileDialog {
        id: fileDialog

        onAccepted: {
            if (fileDialog.selectExisting) {
                console.log("Loading file: " + fileDialog.fileUrl);
                if (!xmlFile.load(fileDialog.fileUrl, keyboardLayout)) {
                    cannotLoadFileDialog.open();
                }
            }
            else {
                saveAction.trigger();
            }
        }
    }

    MessageDialog {
        id: cannotLoadFileDialog

        icon: StandardIcon.Warning
        text: "Cannot load file " + fileDialog.fileUrl
        standardButtons: StandardButton.Ok
    }

    MessageDialog {
        id: cannotSaveFileDialog

        icon: StandardIcon.Warning
        text: "Cannot save file " + fileDialog.fileUrl
        standardButtons: StandardButton.Ok
    }

    XmlFile {
        id: xmlFile
    }

    KeyboardLayout {
        id: keyboardLayout
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        anchors.margins: 1

        acceptedButtons: Qt.LeftButton | Qt.RightButton

        property ComputerKey selectedComputerKey: null
        property bool bindToKeyCode: false
        property point moveOffset

        function updateSelectedComputerKey(mouseEvent) {
            var computerKey = childAt(mouseEvent.x, mouseEvent.y);
            if (computerKey !== null && mouseEvent.buttons === Qt.LeftButton) {
                computerKey.forceActiveFocus();
            }
            else {
                forceActiveFocus();
            }
            mouseArea.selectedComputerKey = computerKey;
            mouseArea.bindToKeyCode = mouseEvent.buttons === Qt.RightButton;
        }

        onPressed: {
            updateSelectedComputerKey(mouse);
            if (mouseArea.selectedComputerKey !== null) {
                mouseArea.moveOffset = Qt.point(
                    mouseArea.selectedComputerKey.x - mouse.x,
                    mouseArea.selectedComputerKey.y - mouse.y);
            }
        }

        onPositionChanged: {
            if (mouseArea.selectedComputerKey !== null) {
                keyboardLayout.moveComputerKey(
                    mouseArea.selectedComputerKey.modelIndex,
                    Math.round((mouse.x + mouseArea.moveOffset.x) / root.scale),
                    Math.round((mouse.y + mouseArea.moveOffset.y) / root.scale)
                );

                updateSelectedComputerKey(mouse);
            }
        }

        onDoubleClicked: {
            if (mouseArea.selectedComputerKey === null) {
                keyboardLayout.addComputerKey(
                    Math.round(mouse.x / root.scale - root.defaultKeySize / 2),
                    Math.round(mouse.y / root.scale - root.defaultKeySize / 2),
                    root.defaultKeySize,
                    root.defaultKeySize,
                    "",
                    0);
            }
            else {
                keyboardLayout.removeComputerKey(mouseArea.selectedComputerKey.modelIndex);
            }

            updateSelectedComputerKey(mouse);
        }

        Connections {
            target: keyboardInput

            onKeyPressed: {
                if (mouseArea.bindToKeyCode && mouseArea.selectedComputerKey !== null) {
                    keyboardLayout.bindComputerKey(
                        mouseArea.selectedComputerKey.modelIndex, keyCode);
                    mouseArea.bindToKeyCode = false;
                }
            }
        }

        Repeater {
            model: keyboardLayout

            delegate: ComputerKey {
                id: computerKey

                x: root.scale * model.x + 1
                y: root.scale * model.y + 1

                width: root.scale * model.width - 2
                height: root.scale * model.height - 2

                label: model.label
                keyCode: model.keyCode

                bindToKeyCode: mouseArea.selectedComputerKey === computerKey
                    && mouseArea.bindToKeyCode

                readonly property var modelIndex: keyboardLayout.modelIndex(index)

                Connections {
                    target: computerKey.labelInput

                    onEditingFinished: {
                        keyboardLayout.renameComputerKey(
                            computerKey.modelIndex, computerKey.labelInput.text);
                    }
                }

                Connections {
                    target: keyboardInput

                    onKeyPressed: {
                        computerKey.press(keyCode);
                    }

                    onKeyReleased: {
                        computerKey.release(keyCode);
                    }
                }
            }
        }
    }

    KeyboardInput {
        id: keyboardInput
    }

    MidiOut {
        id: midiOut

        deviceIndex: midiOutDevicesGroup.current !== null
            ? midiOutDevicesGroup.current.deviceIndex
            : -1
    }

    Connections {
        target: keyboardInput

        onKeyPressed: {
            midiOut.sendMessage(0x90, keyCode, 100);
        }

        onKeyReleased: {
            midiOut.sendMessage(0x80, keyCode, 0);
        }
    }
}
