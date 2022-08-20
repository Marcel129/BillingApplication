import QtQuick 2.0
import QtQuick.Controls 2.0

TextField{
    width: parent.width
    color: "black"
    font.family: "Tahoma"
    font.pixelSize: 15
    horizontalAlignment: "AlignRight"
    text: "Razem do zapłaty: " + "222.22" + "zł"

    background: Rectangle{
        anchors.fill: parent
        border.color: "brown"
        border.width: 1
    }
}

