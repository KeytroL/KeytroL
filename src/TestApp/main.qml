import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2

import KL.Keyboard 1.0


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
                            if (!xmlKeyboardLayout.save(fileDialog.fileUrl, keyboardLayout)) {
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
    }

    FileDialog {
        id: fileDialog

        onAccepted: {
            if (fileDialog.selectExisting) {
                console.log("Loading file: " + fileDialog.fileUrl);
                if (!xmlKeyboardLayout.load(fileDialog.fileUrl, keyboardLayout)) {
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

    XmlKeyboardLayout {
        id: xmlKeyboardLayout
    }

    KeyboardLayout {
        id: keyboardLayout
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent
        anchors.margins: 1

        property Rectangle selectedComputerKey: null
        property int newComputerKeyOffset: 0

        function updateSelectedComputerKey(x, y) {
            var computerKey = childAt(x, y);
            if (computerKey === null) {
                forceActiveFocus();
            }
            else {
                computerKey.forceActiveFocus();
            }
            mouseArea.selectedComputerKey = computerKey;
        }

        onPressed: {
            updateSelectedComputerKey(mouse.x, mouse.y);
        }

        onPositionChanged: {
            if (mouseArea.selectedComputerKey !== null) {
                keyboardLayout.moveComputerKey(
                    mouseArea.selectedComputerKey.modelIndex,
                    Math.round(mouse.x / root.scale - root.defaultKeySize / 2),
                    Math.round(mouse.y / root.scale - root.defaultKeySize / 2)
                );

                updateSelectedComputerKey(mouse.x, mouse.y);
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
                    1 + mouseArea.newComputerKeyOffset);
                ++mouseArea.newComputerKeyOffset;
            }
            else {
                keyboardLayout.removeComputerKey(mouseArea.selectedComputerKey.modelIndex);
            }

            updateSelectedComputerKey(mouse.x, mouse.y);
        }

        Repeater {
            model: keyboardLayout

            delegate: Rectangle {
                antialiasing: false
                border.width: 1
                border.color: selected ? "black" : "lightgray"
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
                    target: keyboard

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

    Keyboard {
        id: keyboard
    }
}
