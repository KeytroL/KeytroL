import QtQuick 2.3


Rectangle {
    id: root

    width: 640
    height: 480

    Rectangle {
        anchors.fill: parent
        anchors.margins: 1

        Repeater {
            model: theKeyboardLayout

            delegate: Rectangle {
                antialiasing: false
                border.width: 1
                border.color: "black"
                radius: 5

                x: 10 * model.x + 1
                y: 10 * model.y + 1

                width: 10 * model.width - 2
                height: 10 * model.height - 2

                Text {
                    anchors.fill: parent
                    anchors.margins: 5

                    text: model.label
                }
            }
        }
    }
}
