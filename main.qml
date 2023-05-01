import QtQuick 2.2
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window{
    id:rootWindow
    height: 700
    width: 1000
    minimumHeight: 300
    minimumWidth: 600
    visible:true
    color: "lightgrey"
    title: "Zielony Kram"
    property bool isHiding: false

    //saving data when the window is closing (to correct)
    onVisibleChanged: {
        if(isHiding){
            myDatabase.saveInvoicesRegister()
            myDatabase.saveCustomers()
            myDatabase.saveSellers()
            myDatabase.saveProducts()
        }
        isHiding = true
    }

    MenuBar{
        id: menuBar
        width: parent.width/5 > 200 ?  200 : parent.width/5 < 100 ? 100 : parent.width/5
        property string __focusedElem: bb1.text

        BarButton{
            id: bb1
            y: parent.height/6 + ( bb1.height + 10)*0
            text: "Rachunek"
            __textBold: menuBar.__focusedElem == text
            onClicked:  {
                 load1.source = "InvoiceScreen.qml"
               menuBar.__focusedElem = text
            }
        }
        BarButton{
            id: bb2
            y: parent.height/6 + ( bb1.height + 10)*1
            text: "Kontrahenci"
            __textBold: menuBar.__focusedElem == text
            onClicked:  {
                 menuBar.__focusedElem = text
                load1.source = "ClientsScreen.qml"
            }
        }
        BarButton{
            id: bb3
            y: parent.height/6 + ( bb1.height + 10)*2
            text: "Produkty"
            __textBold: menuBar.__focusedElem == text
            onClicked:{
                 menuBar.__focusedElem = text
                load1.source = "PlantsScreen.qml"
            }
        }
        BarButton{
            id: bb4
            y: parent.height/6 + ( bb1.height + 10)*3
            text: "Rejestr"
            __textBold: menuBar.__focusedElem == text
            onClicked:{
                 menuBar.__focusedElem = text
                load1.source = "RegisterScreen.qml"
            }
        }
        BarButton{
            id: bb5
            y: (parent.height - height) - parent.height*0.2
            text: "Opcje"
            __textBold: menuBar.__focusedElem == text
            onClicked: {
                load1.source = "OptionsScreen.qml"
                 menuBar.__focusedElem = text
            }
        }
    }

    Loader{
        id:load1
        anchors{
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: menuBar.right
        }
        source: "InvoiceScreen.qml"
    }
}
