import QtQuick 2.2
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window{
    id:root
    height: 600
    width: 800
    minimumHeight: 300
    minimumWidth: 600
    visible:true
    color: "lightgrey"
    title: "Zielony Kram"

    MenuBar{
        id: menuBar
        width: parent.width/5 > 200 ?  200 : parent.width/5 < 100 ? 100 : parent.width/5

        BarButton{
            id: bb1
            y: parent.height/6 + ( bb1.height + 10)*0
            text: "Rachunek"
            onClicked:  load1.source = "InvoiceScreen.qml"
        }
        BarButton{
            id: bb2
            y: parent.height/6 + ( bb1.height + 10)*1
            text: "Kontrahenci"
            onClicked:  load1.source = "ClientsScreen.qml"
        }
        BarButton{
            id: bb3
            y: parent.height/6 + ( bb1.height + 10)*2
            text: "Produkty"
            onClicked:  load1.source = "PlantsScreen.qml"
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


//    Item {
//            anchors{
//                top: parent.top
//                bottom: parent.bottom
//                right: parent.right
//                left: menuBar.right
//            }

//        LineEdit{
//            id: le1
//            anchors{
//                top: parent.top
//                topMargin: 50
//                left: parent.left
//                leftMargin:  50
//            }
//            caption: "Oryginalny tekst"
//            onTextChanged: {
//                my_class_instantiondupa.setText(le1.text)
//                my_txt.text = my_class_instantiondupa.getText()
//            }
//        }
//        LineEdit{
//            id:le2
//            text: le1.text
//            anchors{
//                top: parent.top
//                topMargin: 50
//                left: parent.left
//                leftMargin:  250
//            }
//            caption: "Powielony tekst"
//        }

//        ChooseField{
//            id: myCF
//            anchors{
//                left: parent.left
//                top: parent.top
//                topMargin: 100
//                leftMargin: 50
//            }
//            caption: "Sprzedawca"
//        }

//        Text{
//            id: my_txt
//            anchors{
//                top: myCF.top
//                left: myCF.right
//                leftMargin: 50
//            }
//            font.pixelSize: 20
//            text: my_class_instantiondupa.getText()

//        }

//        ListModel {
//            id: mListModel
//            ListElement {cost: "144"; plant: "krzak"}
//            ListElement {cost: "114";plant: "inny Krzak"}
//            ListElement {cost: "154";plant: "krzak"}
//            ListElement {cost: "174";plant: "inny Krzak"}
//            ListElement {cost: "144";plant: "krzak"}

//        }

//        Component{
//            id: delegComp

//            Rectangle{
//                readonly property ListView delegLv: ListView.view
//                readonly property alias text: delegText1.text
//                id:delegRec
//                anchors{
//                    right: parent.right
//                    left: parent.left
//                }
//                implicitHeight: delegText1. implicitHeight
////                height: index * 7 + 30
////                opacity: 0.5
//                radius: 2
//                border.color: "black"
//                border.width: 1
////                color: lv.currentIndex === index ? "grey" : "white"
////                color: "white"
//                Text{
//                    opacity: 1
//                    id:delegText1
//                    text: model.plant
//                    font.pixelSize: 20
//                    width: 150
//                }
//                Text{
//                    opacity: 1
//                    id:delegText2
//                    text: model.cost
//                    font.pixelSize: 20
//                    anchors.left: delegText1.right
//                }
//                MouseArea{
//                    id: delegMA1
//                    anchors.fill: parent
//                    hoverEnabled: true
//                    onClicked: delegLv.currentIndex = model.index
//                }
//            }
//        }


//        ListView{
//            id: lv
//            highlightMoveDuration: 0
//            height: 150
//            anchors{
//                right: parent.right
//                left: parent.left
//                top: parent.top
//                margins: 10
//                topMargin:  200
//            }
//            model: mListModel
//            delegate: delegComp
//            focus: true
//            clip: true

//            header: Rectangle{
//                anchors{
//                    right: parent.right
//                    left: parent.left
//                }
//                height: 10
//                color: "pink"
//            }
//            highlight: Rectangle{
//                z:3
//                opacity: 0.3
//                anchors{
//                    right: parent.right
//                    left: parent.left
//                }
//                color: "blue"
//            }
//        }
//    }

//    Text{
//        anchors{
//            bottom: parent.bottom
//            left: menuBar.right
//            margins: 20
//        }
//        text: "Current text: " + lv.currentItem.text
//        font.pixelSize: 20
//    }
