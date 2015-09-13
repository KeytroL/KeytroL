import QtQuick 2.3

import KL.Keyboard 1.0


Rectangle {
    id: root

    width: 640
    height: 480

    Keyboard {
        id: keyboard
    }

    Rectangle {
        anchors.fill: parent
        anchors.margins: 1

        MouseArea {
            anchors.fill: parent

            property int offset: 0

            onDoubleClicked: {
                theKeyboardLayout.addComputerKey(
                    Math.round(mouse.x / 10), Math.round(mouse.y / 10),
                    4, 4,
                    String.fromCharCode(65 + offset),
                    1 + offset);
                ++offset;
            }
        }

        Repeater {
            model: theKeyboardLayout

            delegate: Rectangle {
                antialiasing: false
                border.width: 1
                border.color: "black"
                radius: 5

                color: "white"

                x: 10 * model.x + 1
                y: 10 * model.y + 1

                width: 10 * model.width - 2
                height: 10 * model.height - 2

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
}
