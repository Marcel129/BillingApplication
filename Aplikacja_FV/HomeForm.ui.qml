import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    width: 600
    height: 400

    title: qsTr("Home")
    anchors.centerIn: parent
    Label {
        text: qsTr("You are on the home page.")
        transformOrigin: Item.Center
        anchors.centerIn: parent
    }

    Button {
        width: 150
        height: 40
        id: button
        x: parent.width / 2 - width / 2
        y: parent.height * 0.6
        text: qsTr("Generate PDF")

        onPressed: f.createFV();
    }
}
