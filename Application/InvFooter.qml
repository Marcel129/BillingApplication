import QtQuick 2.0
import QtQuick.Controls 2.0

TextField{
    property string __sum: "undefined"
    width: parent.width
    color: "black"
    font.family: "Tahoma"
    font.pixelSize: 15
    horizontalAlignment: "AlignRight"
    text: "Razem do zapłaty: " + __sum + "zł"

    background: Rectangle{
        anchors.fill: parent
        border.color: "#5865F2"
        border.width: 1
        radius: 4
        Rectangle{
            height:  4
            anchors{
                top: parent.top
                right: parent.right
                left: parent.left
                margins: 1
            }
            color: "white"
        }
        Rectangle{
            width: 1
            height:  10
            color: "#5865F2"
            anchors{
                top:parent.top
                left: parent.left
            }
        }
        Rectangle{
            width: 1
            height:  10
            color: "#5865F2"
            anchors{
                top:parent.top
                right: parent.right
            }
        }
    }
}

