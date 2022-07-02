import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
    width: 600
    height: 400

    title: qsTr("Home")
    anchors.centerIn: parent

    Button {
        width: 150
        height: 40
        id: button
        x: 421
        y: 312
        text: qsTr("Generate PDF")

        //onPressed: f.createFV()
    }

    ComboBox {
        id: comboBox
        x: 163
        y: 187
        width: 275
        height: 48
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}
}
##^##*/
