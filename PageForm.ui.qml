import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    id: page
    width: 1000
    height: 600
    property alias element2: element2
    property alias element1: element1
    property alias element: element
    property alias row: row
    contentHeight: 8
    property alias board: board
    property alias page: page



    Rectangle {
        id: rectangle
        color: "#ffffff"
        anchors.fill: parent

        Row {
            id: row
            x: 200
            y: 0
            anchors.right: board.right
            anchors.rightMargin: 0
            anchors.bottom: board.bottom
            anchors.bottomMargin: 400
            transformOrigin: Item.Top
            anchors.left: board.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
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
            x: 200
            y: 100
            width: 600
            height: 400
            color: "#2e8b57"
            border.width: 1
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            objectName: "board"
        }




    }

}













/*##^## Designer {
    D{i:1;anchors_height:200;anchors_width:200;anchors_x:49;anchors_y:89}
}
 ##^##*/
