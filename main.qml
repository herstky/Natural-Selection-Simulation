import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.2

ApplicationWindow {
    visible: true
    visibility: "Maximized"

    title: qsTr("EcoSim")

    Page {
        id: page
        property alias container: container
        property alias element2: element2
        property alias element1: element1
        property alias element: element
        property alias row: row
        contentHeight: 8
        property alias board: board
        property alias page: page
        anchors.fill: parent

        Rectangle {
            id: container
            color: "#ffffff"
            anchors.fill: parent
            objectName: "container"

            Column {
                id: column
                x: 143
                y: -61

                width: 600
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.horizontalCenter: parent.horizontalCenter
                objectName: "column"

                Row {
                    id: row
                    y: 50
                    height: 50
                    anchors.bottom: board.top
                    anchors.bottomMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    transformOrigin: Item.Top
                    objectName: "textRow"

                    Label {
                        id: element2
                        width: 130
                        height: 36
                        text: qsTr("Text")
                        fontSizeMode: Text.HorizontalFit
                        wrapMode: Text.NoWrap
                        font.pixelSize: 18
                        anchors.bottom: parent.bottom
                        verticalAlignment: Text.AlignBottom
                        anchors.bottomMargin: 0
                        objectName: "redCountText"
                    }

                    Label {
                        id: element1
                        width: 130
                        height: 36
                        text: qsTr("Text")
                        fontSizeMode: Text.HorizontalFit
                        wrapMode: Text.WordWrap
                        font.pixelSize: 18
                        anchors.bottom: parent.bottom
                        verticalAlignment: Text.AlignBottom
                        anchors.bottomMargin: 0
                        objectName: "greenCountText"
                    }

                    Label {
                        id: element
                        width: 130
                        height: 36
                        text: qsTr("Text")
                        fontSizeMode: Text.HorizontalFit
                        wrapMode: Text.WordWrap
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 0
                        verticalAlignment: Text.AlignBottom
                        font.pixelSize: 18
                        objectName: "blueCountText"
                    }
                }

                Rectangle {
                    id: board
                    height: 400
                    color: "#2e8b57"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    border.width: 0
                    objectName: "board"
                }

                Row {
                    id: buttonRow
                    height: 50
                    anchors.top: board.bottom
                    anchors.topMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    objectName: "buttonRow"

                    CheckBox {
                        id: animateCheckBox
                        text: qsTr("Animate")
                        font.pointSize: 14
                        checkState: Qt.Checked
                        objectName: "animateCheckBox"
//                        signal qmlToggleAnimation()

                    }
                }
            }
        }
    }
}
