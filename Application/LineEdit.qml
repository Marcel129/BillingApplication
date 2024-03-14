import QtQuick 2.7
import QtQuick.Controls 2.0

Item{
    id:rootItem
    implicitHeight: 35
    implicitWidth: parent.width
    property alias  text: ti1.text
    property alias caption: cap.text
    property alias __disable: ti1.readOnly
    property alias __textColor: ti1.color
    Rectangle{
        id:rootRec
        border.color: "#5865F2"
        border.width: 1
        radius: 4
        anchors.fill: parent

        MouseArea {
            id: ma1
            anchors.fill: parent
            hoverEnabled: true
            cursorShape: Qt.IBeamCursor
            onDoubleClicked: ti1.text = ""
        }

        TextInput{
            id:ti1
            anchors{
                fill: parent
                margins: 2
            }
            font.pixelSize: 18
            verticalAlignment: Text.AlignVCenter
            font.family: "Tahoma"
            leftPadding: 10
        }

        Text{
            id:cap
            anchors{
                bottom: rootRec.top
                bottomMargin: 2
                left: rootRec.left
            }
            font.pixelSize: 15
            font.family: "Raleway"
        }
    }
}
