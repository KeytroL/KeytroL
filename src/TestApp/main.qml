import QtQuick 2.3

import KL.Keyboard 1.0


Rectangle {
    id: root

    width: 640
    height: 480

    readonly property int scale: 10
    readonly property int defaultKeySize: 4

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
                readonly property var modelIndex: keyboardLayout.index(index, 0)

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
