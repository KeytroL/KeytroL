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


Rectangle {
    id: root

    property string label: ""
    property int keyCode: 0

    property bool bindToKeyCode: false

    readonly property TextInput labelInput: labelInput

    antialiasing: false
    border.width: 1
    radius: 5

    border.color: root.activeFocus || labelInput.activeFocus
        ? "black"
        : root.bindToKeyCode
            ? "red"
            : "lightgray"

    color: "white"

    function press(keyCode) {
        if (root.keyCode === keyCode) {
            root.color = "lightgray";
        }
    }

    function release(keyCode) {
        if (root.keyCode === keyCode) {
            root.color = "white";
        }
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_Enter || event.key === Qt.Key_Return) {
            if (root.activeFocus) {
                labelInput.forceActiveFocus();
            }
            else {
                forceActiveFocus();
            }
        }
    }

    TextInput {
        id: labelInput

        anchors.fill: parent
        anchors.margins: 5

        visible: labelInput.activeFocus

        text: root.label
        font.pixelSize: 9
        wrapMode: Text.Wrap
    }

    Text {
        visible: !labelInput.visible

        anchors.fill: labelInput.anchors.fill
        anchors.margins: labelInput.anchors.margins
        font: labelInput.font
        text: labelInput.text
        wrapMode: labelInput.wrapMode
    }
}
