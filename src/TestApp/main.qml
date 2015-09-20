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
                    text: "Save"

                    onTriggered: {
                        if (fileDialog.fileUrl.toString() !== "") {
                            console.log("Saving file: " + fileDialog.fileUrl);
                            if (!xmlKeyboardLayout.save(fileDialog.fileUrl, keyboardLayout)) {
                                cannotSaveFileDialog.open();
                            }
                        }
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
        anchors.fill: parent
        anchors.margins: 1

        property var selectedComputerKey
        property int newComputerKeyOffset: 0

        onPressed: {
            selectedComputerKey = childAt(mouse.x, mouse.y);
        }

        onPositionChanged: {
            if (selectedComputerKey) {
                keyboardLayout.moveComputerKey(
                    selectedComputerKey.modelIndex,
                    Math.round(mouse.x / root.scale - root.defaultKeySize / 2),
                    Math.round(mouse.y / root.scale - root.defaultKeySize / 2)
                );

                selectedComputerKey = childAt(mouse.x, mouse.y);
            }
        }

        onDoubleClicked: {
            var computerKey = childAt(mouse.x, mouse.y);

            if (computerKey === null) {
                keyboardLayout.addComputerKey(
                    Math.round(mouse.x / root.scale - root.defaultKeySize / 2),
                    Math.round(mouse.y / root.scale - root.defaultKeySize / 2),
                    root.defaultKeySize,
                    root.defaultKeySize,
                    String.fromCharCode(65 + newComputerKeyOffset),
                    1 + newComputerKeyOffset);
                ++newComputerKeyOffset;
            }
            else {
                keyboardLayout.removeComputerKey(computerKey.modelIndex);
            }

            selectedComputerKey = childAt(mouse.x, mouse.y);
        }

        Repeater {
            model: keyboardLayout

            delegate: Rectangle {
                readonly property var modelIndex: keyboardLayout.modelIndex(index)

                antialiasing: false
                border.width: 1
                border.color: "black"
                radius: 5

                color: "white"

                x: root.scale * model.x + 1
                y: root.scale * model.y + 1

                width: root.scale * model.width - 2
                height: root.scale * model.height - 2

                Text {
                    anchors.fill: parent
                    anchors.margins: 5

                    text: model.label
                    font.pixelSize: 9
                    wrapMode: Text.Wrap
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
