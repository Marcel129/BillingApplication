import QtQuick 2.0
import QtQuick.Controls 2.0

Item{
    id:rootItem
    implicitHeight: 35
    implicitWidth: parent.width
    property alias  text: ti1.text
    property alias caption: cap.text
    property alias __disable: ti1.readOnly
    Rectangle{
        id:rootRec
        border.color: "brown"
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
            color: focus && !__disable ? "black" : "grey"
//            font.pixelSize: parent.height - 10
            verticalAlignment: Text.AlignVCenter
            font.family: "Tahoma"
        }

        Text{
            id:cap
            anchors{
                bottom: rootRec.top
                bottomMargin: 2
                left: rootRec.left
            }
            font.pixelSize: 15
            font.family: "Times New Roman"
            color: __disable ? "grey" : "black"
        }
    }
}
