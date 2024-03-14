import QtQuick 2.7
import QtQuick.Controls 2.0

Item{
    id:rootItem
    implicitHeight: 35
    implicitWidth: parent.width
    property alias  text: ti1.text
    property alias __HTextAlignment: ti1.horizontalAlignment
    property alias __fontSize: ti1.font.pixelSize
    Rectangle{
        id:rootRec
        border.color: "#5865F2"
        border.width: 2
        anchors.fill: parent

        Text{
            id:ti1
            anchors{
                fill: parent
                margins: 2
            }
            font.pixelSize: 18
            verticalAlignment: Text.AlignVCenter
            font.family: "Tahoma"
            leftPadding: 10
            color: "black"
        }
    }
}
