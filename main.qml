import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.2

ApplicationWindow {
    visible: true
    visibility: "Maximized"

    title: qsTr("EcoSim")

    SwipeView {
        id: swipeView
        anchors.fill: parent

        PageForm {
            id: page
        }
    }
}
