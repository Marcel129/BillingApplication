import QtQuick 2.2
import QtQuick.Controls 2.0

Item {
    id:rootItem
    implicitHeight: 35
    implicitWidth: parent.width
    property alias caption: txt.text
    property alias __model: rootBox.model
    property alias __currentText: rootBox.currentText

    signal clicked()

    ComboBox{
        id:rootBox
        font.pixelSize: 18
        font.family: "Tahoma"
        padding: 0
        anchors.fill: parent

        background: Rectangle{
            anchors.fill: parent
            color: "white"
            radius: 4
            border.color: "#5865F2"
            border.width: 1
        }

    }
    Text{
        id: txt
        anchors{
            left: rootBox.left
            bottom: rootBox.top
            bottomMargin: 2
        }
        font.pixelSize: 15
        font.family: "Raleway"
    }
}
