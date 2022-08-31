import QtQuick 2.0
import QtQuick.Controls 2.0

Button{
    id: m_addButton
    font.pixelSize: 20
    font.family: "Raleway"

    background: Rectangle{
        anchors.fill: parent
        color: "#5865F2"
        border.color: "#5865F2"
        radius: 4
    }

    contentItem: Text {
            text: m_addButton.text
            font: m_addButton.font
            anchors.fill: parent
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
}
