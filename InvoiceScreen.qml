import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

import InvRecords 1.0

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
                caption: "Sprzedawca"
                width:    mainInvData/2
                __model: myDatabase.getSellersNames()
            }
            ChooseField{
                id:buyer
                caption: "Nabywca"
                width:    mainInvData/2
                __model: myDatabase.getCustomersNames()
            }
            ChooseField{
                id:reciper
                caption: "Odbiorca"
                width:    mainInvData/2
                __model:myDatabase.getRecipersNames(buyer.__currentText)
            }
            ChooseField{
                id:payment_method
                caption: "Sposób płatności"
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
                caption: "Miejsce wystawienia rachunku"
                text: myInvoice.getBillingPalce()
            }
            LineEdit{
                id: sales_date
                caption: "Data sprzedaży"
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
                    __textColor: invoice_number_switch.position == 0.0 ? "grey" : "black"
                    text: myInvoice.getInvoiceNumber_slot()
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
            width: 80
            height: plantName.height
            font.family: "Raleway"
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
                plantAmmount.text = ""
                plantPrice.text = ""
                plantRabat.text = "0"
                lv.__sumToPay = myInvoice.getTotalToPay_String()
            }

            background: Rectangle{
                anchors.fill: parent
                color: "#5865F2"
                border.color: "#5865F2"
                radius: 4
            }

            contentItem: Text {
                    text: addButton.text
                    font: addButton.font
                    anchors.fill: parent
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
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
        width: addButton.width
        font.family: "Raleway"
        anchors{
            right: rootItem.right
            top: lv.top
            margins: __generalMargins
            topMargin: 0
        }
        onClicked: {
            if(lv.currentIndex>=0)   myInvoice.removeInvRecordAt(lv.currentIndex)
            lv.__sumToPay = myInvoice.getTotalToPay_String()
        }
        background: Rectangle{
            anchors.fill: parent
            color: "#5865F2"
            border.color: "#5865F2"
            radius: 4
        }

        contentItem: Text {
                text: removePositionButton.text
                font: removePositionButton.font
                anchors.fill: parent
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
    }

    Component{
        id: lvElem

        Rectangle{
            readonly property ListView delegLv: ListView.view
            readonly property int fontSize: 15
            readonly property bool __fontBold: false
            readonly property string __font: "Tahoma"
            readonly property string __fontColor: "black"
            id: elemRootRec
            anchors{
                right: parent.right
                left: parent.left
            }
            implicitHeight: 30
            TextField{
                id:lpElem
                text: model.lp
                height: elemRootRec.height
                width: 40
                font.bold: elemRootRec.__fontBold
                color: __fontColor
                font.family: __font
                font.pixelSize: fontSize
                anchors{
                    top: elemRootRec.top
                    left: elemRootRec.left
                }
                background: InvElem_bck{}
            }
            TextField{
                id:nameElem
                visible: true
                text: model.name
                height: elemRootRec.height
                font.pixelSize: fontSize
                font.bold: elemRootRec.__fontBold
                color: __fontColor
                font.family: __font
                anchors{
                    top: elemRootRec.top
                    left: lpElem.right
                    right: ammountElem.left
                }
                background: InvElem_bck{}
            }
            TextField{
                id:ammountElem
                text: model.ammount
                font.pixelSize: fontSize
                font.bold: elemRootRec.__fontBold
                color: __fontColor
                font.family: __font
                height: elemRootRec.height
                width: 100
                anchors{
                    top: elemRootRec.top
                    right: priceElem.left
                }
                background: InvElem_bck{}
            }
            TextField{
                id:priceElem
                text: model.price
                font.pixelSize: fontSize
                font.bold: elemRootRec.__fontBold
                color: __fontColor
                font.family: __font
                height: elemRootRec.height
                width: 100
                anchors{
                    top: elemRootRec.top
                    right: rabatElem.left
                }
                background: InvElem_bck{}
            }
            TextField{
                id:rabatElem
                text: model.rabat
                font.pixelSize: fontSize
                font.bold: elemRootRec.__fontBold
                color: __fontColor
                font.family: __font
                height: elemRootRec.height
                width: 100
                anchors{
                    top: elemRootRec.top
                    right: elemRootRec.right
                }
                background: InvElem_bck{}
            }
            MouseArea{
                id: delegMA1
                anchors.fill: parent
                hoverEnabled: true
                onClicked: delegLv.currentIndex = model.index
            }
        }
    }

    Component{

        id: lvHeaderElem

        Rectangle{
            id: elemRootRec
            readonly property ListView delegLv: ListView.view
            readonly property int fontSize: 15
            readonly property bool __fontBold: true
            readonly property string __font: "Raleway"
            readonly property string __fontColor: "white"

            anchors{
                right: parent.right
                left: parent.left
            }
            implicitHeight: 30
            TextField{
                id:lpElem
                text: "Lp."
                font.bold: elemRootRec.__fontBold
                horizontalAlignment:  "AlignHCenter"
                color: __fontColor
                font.family: __font
                height: elemRootRec.height
                width: 40
                font.pixelSize: fontSize

                anchors{
                    top: elemRootRec.top
                    left: elemRootRec.left
                }
                background:InvHeaderElem_bck{}

            }
            TextField{
                id:nameElem
                visible: true
                text: "Nazwa"
                height: elemRootRec.height
                color: __fontColor
                horizontalAlignment:  "AlignHCenter"
                font.bold: elemRootRec.__fontBold
                font.pixelSize: fontSize
                font.family: __font
                anchors{
                    top: elemRootRec.top
                    left: lpElem.right
                    right: ammountElem.left
                }
                background: InvHeaderElem_bck{}
            }
            TextField{
                id:ammountElem
                text: "Ilość [szt.]"
                font.pixelSize: fontSize
                color: __fontColor
                height: elemRootRec.height
                horizontalAlignment:  "AlignHCenter"
                font.bold: elemRootRec.__fontBold
                font.family: __font
                width: 100
                anchors{
                    top: elemRootRec.top
                    right: priceElem.left
                }
                background: InvHeaderElem_bck{}
            }
            TextField{
                id:priceElem
                text: "Cena [zł]"
                font.pixelSize: fontSize
                horizontalAlignment:  "AlignHCenter"
                color: __fontColor
                height: elemRootRec.height
                font.bold: elemRootRec.__fontBold
                font.family: __font
                width: 100
                anchors{
                    top: elemRootRec.top
                    right: rabatElem.left
                }
                background: InvHeaderElem_bck{}
            }
            TextField{
                id:rabatElem
                text: "Rabat [%]"
                color: __fontColor
                font.pixelSize: fontSize
                horizontalAlignment:  "AlignHCenter"
                font.family: __font
                font.bold: elemRootRec.__fontBold
                height: elemRootRec.height
                width: 100
                anchors{
                    top: elemRootRec.top
                    right: elemRootRec.right
                }
                background: InvHeaderElem_bck{}
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
        property string __sumToPay: myInvoice.getTotalToPay_String()
        id: lv
        highlightMoveDuration: 0
        anchors{
            right: removePositionButton.left
            left: rootItem.left
            top: addPlantRoot.bottom
            bottom: generateInvoiceButton.top
            margins: __generalMargins
            topMargin: 25
        }
        model: InvRecListModel {
            mInvoice: myInvoice
        }
        delegate:lvElem
        focus: true
        clip: true

        header:  lvHeaderElem
        footer: InvFooter{
            id: invFoot
            __sum: lv.__sumToPay
        }

        highlight: Rectangle{
            z:3
            opacity: 0.3
            anchors{
                right: parent.right
                left: parent.left
            }
            color: "#5865F2"
        }
    }

    Text{
        id:recordsCaption
        anchors{
            bottom: lv.top
            bottomMargin: 2
            left: lv.left
        }
        color: "black"
        font.pixelSize: 15
        font.family: "Raleway"
        text:"Pozycje na rachunku"
    }

    Button{
        id: generateInvoiceButton
        text: "Utwórz"
        font.pixelSize: 20
        height: plantPrice.height
        font.family: "Raleway"
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
            myInvoice.setInvoiceNumber_slot(invoice_number.text)

            myInvoice.createInvoice()
            invoice_number.text = myInvoice.getInvoiceNumber_slot()
        }
        background: Rectangle{
            anchors.fill: parent
            color: "#5865F2"
            border.color: "#5865F2"
            radius: 4
        }

        contentItem: Text {
                text: generateInvoiceButton.text
                font: addButton.font
                anchors.fill: parent
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
    }
}
