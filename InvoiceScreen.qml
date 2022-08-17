import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3

Item {
    id:rootItem
    anchors.fill: parent

    readonly property int __spacing: 25
    readonly property int __generalMargins: 15
    Item{
        id:mainInvData
        height: 250
        anchors{
            top:parent.top
            left:parent.left
            right: parent.right
        }

        Column{
            id:leftColumn
            anchors{
                top: mainInvData.top
                bottom: mainInvData.bottom
                left: mainInvData.left
                right: mainInvData.horizontalCenter
                margins : __generalMargins
                topMargin: 30
            }
            spacing: __spacing
            ChooseField{
                id:seller
                caption: "Sprzedawca:"
                width:    mainInvData/2
                 __model: myDatabase.getSellersNames()
            }
            ChooseField{
                id:buyer
                caption: "Nabywca:"
                width:    mainInvData/2
                __model: myDatabase.getCustomersNames()
            }
            ChooseField{
                id:reciper
                caption: "Odbiorca:"
                width:    mainInvData/2
                __model:myDatabase.getRecipersNames(buyer.__currentText)
            }
            ChooseField{
                id:payment_method
                caption: "Sposób płatności:"
                width:    mainInvData/2
                 __model: myDatabase.getPaymentMethods()
            }
        }

        Column{
            id: rightColumn
            anchors{
                top: mainInvData.top
                left: leftColumn.right
                right: mainInvData.right
                bottom: mainInvData.bottom
                margins : __generalMargins
                topMargin: 30
            }
            spacing: __spacing
            LineEdit{
                id: place_of_billing
                caption: "Miejsce wystawienia rachunku:"
                text: myInvoice.getBillingPalce()
            }
            LineEdit{
                id: sales_date
                caption: "Data sprzedaży:"
                text: myInvoice.getSellingDate_String()
            }
            Row{
                id:my_row
                width: parent.width
                Switch{
                    id:invoice_number_switch
                    anchors{
                        verticalCenter: invoice_number.verticalCenter
                    }
                }
                LineEdit{
                    id: invoice_number
                    caption: "Numer rachunku (faktury)"
                    width: rightColumn.width - invoice_number_switch.width
                    __disable: invoice_number_switch.position == 0.0
                }
            }
        }
    }
    Item{
        id:addPlantRoot
        anchors{
            top: mainInvData.bottom
            left: mainInvData.left
            right: mainInvData.right
            margins: __generalMargins
            topMargin: 40
        }
        height: plantName.height

        Button{
            id: addButton
            text: "Dodaj"
            font.pixelSize: 20
            height: plantName.height
            font.family: "Times New Roman"
            anchors{
                right: addPlantRoot.right
                top: addPlantRoot.top
                leftMargin: __generalMargins
            }
            onClicked: {
                myInvoice.addRecord(plantName.__currentText,
                                    plantAmmount.text,
                                    plantPrice.text,
                                    plantRabat.text)
            }
        }

        LineEdit{
            id:plantRabat
            caption: "Rabat [%]"
            width: 70
            anchors{
                top: addPlantRoot.top
                right: addButton.left
                margins: __generalMargins
                topMargin: 0
            }
        }

        LineEdit{
            id:plantPrice
            caption: "Cena [zł]"
            width: 70
            anchors{
                top: addPlantRoot.top
                right: plantRabat.left
                margins: __generalMargins
                topMargin: 0
            }
        }

        LineEdit{
            id:plantAmmount
            caption: "Ilość"
            width: 70
            anchors{
                top: addPlantRoot.top
                right: plantPrice.left
                margins: __generalMargins
                topMargin: 0
            }
        }

        ChooseField{
            id:plantName
            caption: "Nazwa"
            __model: myDatabase.getProductsPolishNames()
            anchors{
                top: addPlantRoot.top
                left: addPlantRoot.left
                right: plantAmmount.left
                margins: __generalMargins
                topMargin: 0
                leftMargin: 0
            }
        }

    }

    Button{
        id: removePositionButton
        text: "Usuń"
        font.pixelSize: 20
        height: plantPrice.height
        font.family: "Times New Roman"
        anchors{
            right: rootItem.right
            top: addPlantRoot.bottom
            margins: __generalMargins
        }
    }

    ListModel {
        id: mListModel
        ListElement {name: "Berberys"; price: 146.3; ammount: 15; rabat: 20}
    }

    Component{
        id: lvElem

        Rectangle{
            readonly property ListView delegLv: ListView.view
//            readonly property alias text: delegText1.text
            id: elemRootRec
            anchors{
                right: parent.right
                left: parent.left
            }
            implicitHeight: lpElem. implicitHeight
            radius: 2
            border.color: "black"
            border.width: 1
            //                color: lv.currentIndex === index ? "grey" : "white"
            //                color: "white"
            Text{
                opacity: 1
                id:lpElem
                text: "1"
                font.pixelSize: 20
                anchors{
                    top: elemRootRec.top
                    left: elemRootRec.left
                }
            }
            Text{
                opacity: 1
                id:nameElem
                text: model.name
                font.pixelSize: 20
                anchors{
                    top: elemRootRec.top
                    right: lpElem.left
                }
            }
            Text{
                opacity: 1
                id:priceElem
                text: model.price
                font.pixelSize: 20
                anchors{
                    top: elemRootRec.top
                    right: nameElem.left
                }
            }
            Text{
                opacity: 1
                id:ammountElem
                text: model.ammount
                font.pixelSize: 20
                anchors{
                    top: elemRootRec.top
                    right: priceElem.left
                }
            }
            Text{
                opacity: 1
                id:rabatElem
                text: model.rabat
                font.pixelSize: 20
                anchors{
                    top: elemRootRec.top
                    right: ammountElem.left
                }
            }
            MouseArea{
                id: delegMA1
                anchors.fill: parent
                hoverEnabled: true
                onClicked: delegLv.currentIndex = model.index
            }
        }
    }

    ListView{
        id: lv
        highlightMoveDuration: 0
        anchors{
            right: removePositionButton.left
            left: rootItem.left
            top: addPlantRoot.bottom
            bottom: generateInvoiceButton.top
            margins: __generalMargins
        }
        model: mListModel
        delegate: lvElem
        focus: true
        clip: true

        header: Rectangle{
            anchors{
                right: parent.right
                left: parent.left
            }
            height: 10
            color: "pink"
        }
        highlight: Rectangle{
            z:3
            opacity: 0.3
            anchors{
                right: parent.right
                left: parent.left
            }
            color: "blue"
        }
    }




    Button{
        id: generateInvoiceButton
        text: "Utwórz"
        font.pixelSize: 20
        height: plantPrice.height
        font.family: "Times New Roman"
        anchors{
            right: rootItem.right
            bottom: rootItem.bottom
            margins: __generalMargins
        }
        onClicked: {
            myInvoice.setSeller(seller.__currentText)
            myInvoice.setBuyer(buyer.__currentText)
            myInvoice.setRecip(reciper.__currentText)
            myInvoice.setPaymentMethod(payment_method.__currentText)
            myInvoice.setBillingPalce(place_of_billing.text)
            myInvoice.setSaleDate(sales_date.text)
            myInvoice.createInvoice()
        }
    }
}
