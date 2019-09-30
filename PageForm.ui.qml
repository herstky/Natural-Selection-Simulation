import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    width: 1000
    height: 600
    property alias container: container
    property alias element2: element2
    property alias element1: element1
    property alias element: element
    property alias row: row
    contentHeight: 8
    property alias board: board
    property alias page: page

    Column {
        id: container
        x: 200
        y: 0
        width: 600
        spacing: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        objectName: "container"

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
                width: 100
                height: 36
                text: qsTr("Text")
                font.pixelSize: 18
                anchors.bottom: parent.bottom
                verticalAlignment: Text.AlignBottom
                anchors.bottomMargin: 0
                objectName: "redCountText"
            }

            Label {
                id: element1
                width: 100
                height: 36
                text: qsTr("Text")
                font.pixelSize: 18
                anchors.bottom: parent.bottom
                verticalAlignment: Text.AlignBottom
                anchors.bottomMargin: 0
                objectName: "greenCountText"
            }

            Label {
                id: element
                width: 100
                height: 36
                text: qsTr("Text")
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
    }
}

