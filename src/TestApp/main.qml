import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2

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
                        property int deviceIndex: index

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

        property Rectangle selectedComputerKey: null
        property bool bindToKeyCode: false

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
        }

        onPositionChanged: {
            if (mouseArea.selectedComputerKey !== null) {
                keyboardLayout.moveComputerKey(
                    mouseArea.selectedComputerKey.modelIndex,
                    Math.round(mouse.x / root.scale - root.defaultKeySize / 2),
                    Math.round(mouse.y / root.scale - root.defaultKeySize / 2)
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

            delegate: Rectangle {
                antialiasing: false
                border.width: 1
                border.color: activeFocus || computerKeyLabelInput.activeFocus
                    ? "black"
                    : selected && mouseArea.bindToKeyCode
                        ? "red"
                        : "lightgray"
                radius: 5

                color: "white"

                x: root.scale * model.x + 1
                y: root.scale * model.y + 1

                width: root.scale * model.width - 2
                height: root.scale * model.height - 2

                readonly property var modelIndex: keyboardLayout.modelIndex(index)

                readonly property bool selected: mouseArea.selectedComputerKey !== null
                    && mouseArea.selectedComputerKey.modelIndex === modelIndex

                Keys.onPressed: {
                    if (event.key == Qt.Key_Enter || event.key == Qt.Key_Return) {
                        if (activeFocus) {
                            computerKeyLabelInput.forceActiveFocus();
                        }
                        else {
                            forceActiveFocus();
                        }
                    }
                }

                Text {
                    id: computerKeyLabel

                    anchors.fill: parent
                    anchors.margins: 5
                    visible: !computerKeyLabelInput.visible

                    text: model.label
                    font.pixelSize: 9
                    wrapMode: Text.Wrap
                }

                TextInput {
                    id: computerKeyLabelInput

                    visible: computerKeyLabelInput.activeFocus

                    anchors.fill: computerKeyLabel.anchors.fill
                    anchors.margins: computerKeyLabel.anchors.margins
                    font: computerKeyLabel.font
                    text: computerKeyLabel.text
                    wrapMode: computerKeyLabel.wrapMode

                    onEditingFinished: {
                        keyboardLayout.renameComputerKey(
                            modelIndex, computerKeyLabelInput.text);
                    }
                }

                Connections {
                    target: keyboardInput

                    onKeyPressed: {
                        if (model.keyCode == keyCode) {
                            color = "lightgray";
                        }
                    }

                    onKeyReleased: {
                        if (model.keyCode == keyCode) {
                            color = "white";
                        }
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
