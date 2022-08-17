import QtQuick 2.0

Item{
    id:bb
    property alias text: tx1.text
    height: 40
    anchors{
        left: parent.left
        right: parent.right
    }
    signal clicked
    Rectangle{
        id: rec1
        color: "green"
        border.color: "darkgreen"
        border.width: 2
        anchors{
            fill:parent
        }
        Text {
            id: tx1
            color: "#ebed0e"
            font.pixelSize: 25
            anchors{
                centerIn: parent
                fill: parent
            }
            horizontalAlignment: Text.AlignHCenter
            x: parent.width - width
            verticalAlignment: Text.AlignVCenter
            font.wordSpacing: 1
            font.family: "Times New Roman"
            //        font.bold: ma_bb.containsMouse
        }

        PropertyAnimation{
            id: animUp
            target: rec1
            property: "anchors.topMargin"
            to: -3
            duration: 150
        }

        PropertyAnimation{
            id: animDown
            target: rec1
            property: "anchors.topMargin"
            to: 0
            duration: 150
        }

        MouseArea{
            anchors.fill: parent
            id: ma_bb
            hoverEnabled: true
            //            onHoveredChanged:  containsMouse ? animUp.start() : animDown.start()
            onHoveredChanged:  containsMouse ? animUp.start() : animDown.start()
            cursorShape: Qt.PointingHandCursor
            onClicked: bb.clicked()
        }
    }
}
