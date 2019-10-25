import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

ApplicationWindow {
    width: 800
    height: 600
    visible: true
    visibility: "Maximized"

    title: qsTr("EcoSim")


    Rectangle {
        id: container
        color: "#ffffff"
        anchors.fill: parent
        objectName: "container"

        Column {
            id: column
            width: 600
            transformOrigin: Item.Center
            spacing: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter
            objectName: "column"

            RowLayout {
                id: textRow
                height: 50
                Layout.fillHeight: false
                Layout.fillWidth: true
                layoutDirection: Qt.LeftToRight
                spacing: 2
                objectName: "textRow"

                Label {
                    id: label1
                    height: 22
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: qsTr("Text")
                    fontSizeMode: Text.HorizontalFit
                    wrapMode: Text.NoWrap
                    font.pixelSize: 18
                    verticalAlignment: Text.AlignBottom
                    objectName: "label1"
                }

                Label {
                    id: label2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: qsTr("Text")
                    fontSizeMode: Text.HorizontalFit
                    wrapMode: Text.WordWrap
                    font.pixelSize: 18
                    verticalAlignment: Text.AlignBottom
                    objectName: "label2"
                }

                Label {
                    id: label3
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    text: qsTr("Text")
                    fontSizeMode: Text.HorizontalFit
                    wrapMode: Text.WordWrap
                    verticalAlignment: Text.AlignBottom
                    font.pixelSize: 18
                    objectName: "label3"
                }
            }

            Rectangle {
                id: board
                height: 400
                width: 600
                color: "steelblue"
                border.width: 0
                objectName: "board"
            }

            RowLayout {
                id: buttonRow
                height: 80
                transformOrigin: Item.Center
                Layout.fillHeight: false
                Layout.fillWidth: true
                objectName: "buttonRow"


                Button {
                    id: playPauseButton
                    width: 60
                    text: qsTr("Play")
                    font.pointSize: 14
                    objectName: "playPauseButton"
                }

                ColumnLayout {
                    id: progressColumn

                    ProgressBar {
                        id: progressBar
                        height: 36
                        Layout.fillWidth: true
                        value: 0
                        objectName: "progressBar"
                    }

                    Text {
                        id: progressBarLabel
                        text: qsTr("Generation Progress")
                        horizontalAlignment: Text.AlignHCenter
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        Layout.fillWidth: true
                        font.weight: Font.Normal
                        font.pixelSize: 16
                    }
                }

                CheckBox {
                    id: animateCheckBox
                    width: 80
                    text: qsTr("Animate")
                    font.pointSize: 12
                    checkState: Qt.Checked
                    objectName: "animateCheckBox"
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:3;anchors_y:"-61"}D{i:11;anchors_height:400;anchors_width:200}D{i:10;anchors_height:400;anchors_width:200}
}
##^##*/
