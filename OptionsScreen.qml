import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    anchors.fill: parent
    anchors.margins: 15

    LineEdit{
        id:resourcesPathField
        caption: "Ścieżka katalogu z zasobami"
        anchors{
            top: parent.top
            topMargin: 20
            left: parent.left
            right:parent.right
        }
    }
    LineEdit{
        id: invoicesPathField
        caption: "Ścieżka do zapisu rachunków"
        anchors{
            top: resourcesPathField.bottom
            topMargin: 25
            left: parent.left
            right:parent.right
        }
    }
    Button{
        id:saveOptionsButton
        anchors{
            bottom: parent.bottom
            right: parent.right
        }
        text: "Zapisz"
        font.pixelSize: 20

        background: Rectangle{
            anchors.fill: parent
            color: "#5865F2"
            border.color: "#5865F2"
            radius: 4
        }

        contentItem: Text {
            text: saveOptionsButton.text
            font: saveOptionsButton.font
            anchors.fill: parent
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}

