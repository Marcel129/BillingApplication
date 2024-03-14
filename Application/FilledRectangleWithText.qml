import QtQuick 2.6
import QtQuick.Controls 2.0

Item {
    id:rootItem
    implicitHeight: 35
    implicitWidth: parent.width
    property alias __text: txtField.text
    property alias __hTextAlignment: txtField.horizontalAlignment
    property alias __fontBold: txtField.font.bold
    Rectangle{
        id: rootRec
        anchors {
            fill: parent
        }
        height: 30
        color: "#5865F2"

        Text{
            id:txtField
            color: "white"
            font.family: "Raleway"
            font.pixelSize: 18
            anchors{
                fill: parent
            }
            leftPadding: 10
            rightPadding: 10
            verticalAlignment: Text.AlignVCenter
        }
    }
}
