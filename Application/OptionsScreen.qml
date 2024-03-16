import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.3

Item {
    anchors.fill: parent
    anchors.margins: 15
    readonly property int __spacing: 25
    readonly property int __generalMargins: 15

    MButton{
        id: checkUpdate
        text: "Aktualizuj"
        width: 110
        anchors{
            left: parent.left
            top: parent.top
            margins: __generalMargins
            topMargin: 10
        }
        onClicked: {
            myDatabase.updateAvailable() ? msBox_actualizationAvailable.open() : msBox_noActualization.open()
        }
    }

    MessageDialog {
        id: msBox_noActualization
        title: "Aktualizacja"
        text: "Program jest zaktualizowany do najnowszej wersji."
        standardButtons: StandardButton.Ok
        onAccepted: {
            close()
        }
    }

    MessageDialog {
        id: msBox_actualizationAvailable
        title: "Aktualizacja"
        text: "Dostępna jest aktualizacja programu. Czy chcesz ją teraz pobrać?"
        standardButtons: StandardButton.Yes | StandardButton.No
        onYes: {
            close()
        }
        onNo:{
            close()
        }
    }

//    LineEdit{
//        id:resourcesPathField
//        caption: "Ścieżka katalogu z zasobami"
//        anchors{
//            top: parent.top
//            topMargin: 20
//            left: parent.left
//            right:parent.right
//        }
//    }
//    LineEdit{
//        id: invoicesPathField
//        caption: "Ścieżka do zapisu rachunków"
//        anchors{
//            top: resourcesPathField.bottom
//            topMargin: 25
//            left: parent.left
//            right:parent.right
//        }
//    }
//    Button{
//        id:saveOptionsButton
//        anchors{
//            bottom: parent.bottom
//            right: parent.right
//        }
//        text: "Zapisz"
//        font.pixelSize: 20

//        background: Rectangle{
//            anchors.fill: parent
//            color: "#5865F2"
//            border.color: "#5865F2"
//            radius: 4
//        }

//        contentItem: Text {
//            text: saveOptionsButton.text
//            font: saveOptionsButton.font
//            anchors.fill: parent
//            color: "white"
//            horizontalAlignment: Text.AlignHCenter
//            verticalAlignment: Text.AlignVCenter
//        }
//    }
}

