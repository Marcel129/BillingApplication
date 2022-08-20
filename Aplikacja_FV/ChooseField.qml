import QtQuick 2.2
import QtQuick.Controls 2.0

Item {
    signal clicked()

    property alias caption: txt.text
    property alias __model: rootBox.model
    property alias __currentText: rootBox.currentText

    id:rootItem
    implicitHeight: 35
    implicitWidth: parent.width

    ComboBox{
        id:rootBox
        font.pixelSize: rootBox.height - 18
        font.family: "Tahoma"
        padding: 0
        anchors.fill: parent

        background: Rectangle{
            anchors.fill: parent
            color: "white"
            radius: 4
            border.color: "brown"
            border.width: 1
        }

        onAccepted: rootItem.clicked();

    }
    Text{
        id: txt
        anchors{
            left: rootBox.left
            bottom: rootBox.top
            bottomMargin: 2
        }
        font.pixelSize: 15
        font.family: "Times New Roman"
    }
}
