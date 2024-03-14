import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.3

import InvoicesRegister 1.0

Item {
    id:rootItem
    anchors.fill: parent
    readonly property int __spacing: 25
    readonly property int __generalMargins: 15

    Item{
        id: listMainElem
        anchors{
            left:rootItem.left
            right:rootItem.right
            top: rootItem.top
        }

        height: rootItem.height*0.4

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
                    id:invoiceNumberElem
                    text: model.invoiceNumber
                    font.pixelSize: fontSize
                    font.bold: elemRootRec.__fontBold
                    color: __fontColor
                    font.family: __font
                    height: elemRootRec.height
                    width: elemRootRec.width *0.15
                    anchors{
                        top: elemRootRec.top
                        left: lpElem.right
                    }
                    background: InvElem_bck{}
                }
                TextField{
                    id:customerElem
                    text: model.buyer
                    font.pixelSize: fontSize
                    font.bold: elemRootRec.__fontBold
                    color: __fontColor
                    font.family: __font
                    height: elemRootRec.height
                    width: elemRootRec.width *0.3
                    anchors{
                        top: elemRootRec.top
                        left: invoiceNumberElem.right
                    }
                    background: InvElem_bck{}
                }
                TextField{
                    id:paymentMethodElem
                    visible: true
                    text: model.peymantMethod
                    height: elemRootRec.height
                    font.pixelSize: fontSize
                    font.bold: elemRootRec.__fontBold
                    color: __fontColor
                    font.family: __font
                    anchors{
                        top: elemRootRec.top
                        left: customerElem.right
                        right: dateElem.left
                    }
                    background: InvElem_bck{}
                }
                TextField{
                    id:dateElem
                    text: model.date
                    font.pixelSize: fontSize
                    font.bold: elemRootRec.__fontBold
                    color: __fontColor
                    font.family: __font
                    height: elemRootRec.height
                    width: elemRootRec.width *0.25
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
                    id: invoiceNumberElem
                    visible: true
                    text: "Nr faktury"
                    height: elemRootRec.height
                    color: __fontColor
                    horizontalAlignment:  "AlignHCenter"
                    font.bold: elemRootRec.__fontBold
                    font.pixelSize: fontSize
                    font.family: __font
                    width: elemRootRec.width *0.15
                    anchors{
                        top: elemRootRec.top
                        left: lpElem.right
                    }
                    background: InvHeaderElem_bck{}
                }
                TextField{
                    id:customerElem
                    text: "Nabywca"
                    font.pixelSize: fontSize
                    color: __fontColor
                    height: elemRootRec.height
                    horizontalAlignment:  "AlignHCenter"
                    font.bold: elemRootRec.__fontBold
                    font.family: __font
                    width: elemRootRec.width *0.3
                    anchors{
                        top: elemRootRec.top
                        left: invoiceNumberElem.right
                    }
                    background: InvHeaderElem_bck{}
                }
                TextField{
                    id:paymentMethodElem
                    text: "Płatność"
                    font.pixelSize: fontSize
                    horizontalAlignment:  "AlignHCenter"
                    color: __fontColor
                    height: elemRootRec.height
                    font.bold: elemRootRec.__fontBold
                    font.family: __font
                    anchors{
                        top: elemRootRec.top
                        left: customerElem.right
                        right: dateElem.left
                    }
                    background: InvHeaderElem_bck{}
                }
                TextField{
                    id:dateElem
                    text: "Data wystawienia"
                    color: __fontColor
                    font.pixelSize: fontSize
                    horizontalAlignment:  "AlignHCenter"
                    font.family: __font
                    font.bold: elemRootRec.__fontBold
                    height: elemRootRec.height
                    width: elemRootRec.width *0.25
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
            id: lv
            highlightMoveDuration: 0
            anchors{
                right: removePositionButton.left
                left: listMainElem.left
                top: removePositionButton.top
                bottom: listMainElem.bottom
                margins: __generalMargins
                topMargin: 0
            }

            model: RegisterRecListModel{
                mDatabase: myDatabase
            }

            delegate:lvElem
            focus: true
            clip: true

            header:  lvHeaderElem

            highlight: Rectangle{
                z:3
                opacity: 0.3
                anchors{
                    right: parent.right
                    left: parent.left
                }
                color: "#5865F2"
            }
            onCurrentIndexChanged: {
                invoiceDetailsHeader.__text = "Szczegóły rachunku " + myDatabase.getInvoiceNumber_rev(lv.currentIndex)
                invoiceDetailsHeaderSeller.__text = "Wystawił: " + myDatabase.getSellerName_rev(lv.currentIndex)

                buyerName.text =  myDatabase.getCustomerName_rev(lv.currentIndex)
                buyerAdress.text =  myDatabase.getCustomerAdress1_rev(lv.currentIndex)
                buyerAdress2.text =  myDatabase.getCustomerAdress2_rev(lv.currentIndex)
                buyerNIP.text = "NIP: " + myDatabase.getCustomerNIP_rev(lv.currentIndex)

                reciperName.text = myDatabase.getReciperName_rev(lv.currentIndex)
                reciperAdress.text = myDatabase.getReciperAdress1_rev(lv.currentIndex)
                reciperAdress2.text = myDatabase.getReciperAdress2_rev(lv.currentIndex)

                billingDate.text = myDatabase.getBillingDate_rev(lv.currentIndex)
                paymentMethod.text = myDatabase.getPaymentMethod_rev(lv.currentIndex)
                sumToPay.text = myDatabase.getTotalBillingPrice_rev(lv.currentIndex)+ " zł"
            }
        }

        MButton{
            id: removePositionButton
            text: "Usuń"
            width: 80
            anchors{
                right: listMainElem.right
                top: listMainElem.top
                margins: __generalMargins
                topMargin: 10
            }
            onClicked: {
                messageDialog.open()
            }
        }

        MessageDialog {
            id: messageDialog
            title: "Ostrzeżenie"
            text: "Czy na pewno chcesz usunąć pozycję z bazy? Ta decyzja jest nieodwracalna"
            standardButtons: StandardButton.Yes | StandardButton.No
            onYes: {
                myDatabase.removeInvoiceFromReversedRegisterAt(lv.currentIndex)
                close()
            }
            onNo:{
                close()
            }
        }
    }

    Item {
        id: invoiceDetailsRootItem

        anchors{
            top:  listMainElem.bottom
            bottom: rootItem.bottom
            right: listMainElem.right
            rightMargin: 110
            left: listMainElem.left
            margins: __generalMargins
        }

        FilledRectangleWithText{
            id: invoiceDetailsHeader
            anchors {
                top:invoiceDetailsRootItem.top
                left: invoiceDetailsRootItem.left
            }
            width: invoiceDetailsRootItem.width*0.5
            height: 30
            __fontBold: true
            __hTextAlignment: Text.AlignLeft
        }

        FilledRectangleWithText{
            id: invoiceDetailsHeaderSeller
            anchors {
                top:invoiceDetailsRootItem.top
                left: invoiceDetailsHeader.right
                right: invoiceDetailsRootItem.right
            }
            height: 30
            __fontBold: true
            __text:"Wystawił: "
            __hTextAlignment: Text.AlignRight
        }

        Item{
            id:invoiceMainData
            anchors{
                top: invoiceDetailsHeader.bottom
                left: invoiceDetailsHeader.left
                //                bottom: invoiceDetailsRootItem.bottom
                right: invoiceDetailsHeader.right
            }
            height:150-3*2-2
            FilledRectangleWithText{
                id: buyerMainLabel
                anchors {
                    top:invoiceMainData.top
                    left: invoiceMainData.left
                    right: invoiceMainData.right
                }
                height: 30
                __fontBold: true
                __text:"Dane nabywcy"
                __hTextAlignment: Text.AlignHCenter
            }
            LineEditReadOnly{
                id:buyerName
                anchors {
                    top:buyerMainLabel.bottom
                    left: invoiceMainData.left
                    right: invoiceMainData.right
                }
                height: 30
                text: "NAZWA NABYWCY"
                __fontSize: 15
            }
            LineEditReadOnly{
                id:buyerAdress
                anchors {
                    top:buyerName.bottom
                    left: invoiceMainData.left
                    right: invoiceMainData.right
                    topMargin: -2
                }
                height: 30
                text: "Adres"
                __fontSize: 15
            }
            LineEditReadOnly{
                id:buyerAdress2
                anchors {
                    top:buyerAdress.bottom
                    left: invoiceMainData.left
                    right: invoiceMainData.right
                    topMargin: -2
                }
                height: 30
                text: "Adres2"
                __fontSize: 15
            }
            LineEditReadOnly{
                id:buyerNIP
                anchors {
                    top:buyerAdress2.bottom
                    left: invoiceMainData.left
                    right: invoiceMainData.right
                    topMargin: -2
                }
                height: 30
                text: "NIP: " + "xxxxxxxx"
                __fontSize: 15
            }
        }

        Item{
            id:invoiceMainData2
            anchors{
                top: invoiceDetailsHeaderSeller.bottom
                left: invoiceDetailsHeaderSeller.left
                //                bottom: invoiceDetailsRootItem.bottom
                right: invoiceDetailsHeaderSeller.right
                leftMargin: -2
            }

            FilledRectangleWithText{
                id: reciperMainLabel
                anchors {
                    top:invoiceMainData2.top
                    left: invoiceMainData2.left
                    right: invoiceMainData2.right
                }
                height: 30
                __fontBold: true
                __text:"Dane odbiorcy"
                __hTextAlignment: Text.AlignHCenter
            }
            LineEditReadOnly{
                id:reciperName
                anchors {
                    top:reciperMainLabel.bottom
                    left: invoiceMainData2.left
                    right: invoiceMainData2.right
                }
                height: 30
                text: "NAZWA ODBIORCY"
                __fontSize: 15
            }
            LineEditReadOnly{
                id:reciperAdress
                anchors {
                    top:reciperName.bottom
                    left: invoiceMainData2.left
                    right: invoiceMainData2.right
                    topMargin: -2
                }
                height: 30
                text: "Adres"
                __fontSize: 15
            }
            LineEditReadOnly{
                id:reciperAdress2
                anchors {
                    top:reciperAdress.bottom
                    left: invoiceMainData2.left
                    right: invoiceMainData2.right
                    topMargin: -2
                }
                height: 30
                text: "Adres2"
                __fontSize: 15
            }
            LineEditReadOnly{
                id:reciperAdress3
                anchors {
                    top:reciperAdress2.bottom
                    left: invoiceMainData2.left
                    right: invoiceMainData2.right
                    topMargin: -2
                }
                height: 30
                text: "-"
                __fontSize: 15
            }
        }

        Item{
            id:otherInvoiceData
            anchors{
                top: invoiceMainData.bottom
                left: invoiceMainData.left
                topMargin: 7
            }
            width: 500
            height: 90

            FilledRectangleWithText{
                id: billingDateLabel
                anchors {
                    top:otherInvoiceData.top
                    left: otherInvoiceData.left
                }
                height: 30
                __fontBold: true
                __text:"Data wystawienia: "
                __hTextAlignment: Text.AlignHCenter
                width: 200
            }
            LineEditReadOnly{
                id:billingDate
                anchors {
                    top:otherInvoiceData.top
                    left: billingDateLabel.right
                    right: otherInvoiceData.right
                }
                height: 30
                text: "XXXXXX"
                __fontSize: 15
            }


            FilledRectangleWithText{
                id: paymentMethodLabel
                anchors {
                    top:billingDateLabel.bottom
                    left: otherInvoiceData.left
                    right: billingDateLabel.right
                    topMargin: -2
                }
                height: 30
                __fontBold: true
                __text:"Sposób płatności:  "
                __hTextAlignment: Text.AlignHCenter
            }
            LineEditReadOnly{
                id:paymentMethod
                anchors {
                    top:paymentMethodLabel.top
                    left: paymentMethodLabel.right
                    right: otherInvoiceData.right
                }
                height: 30
                width: 80
                text: "XXXXXX"
                __fontSize: 15
            }


            FilledRectangleWithText{
                id: sumToPayLabel
                anchors {
                    top:paymentMethodLabel.bottom
                    left: otherInvoiceData.left
                    right: billingDateLabel.right
                    topMargin: -2
                }
                height: 30
                __fontBold: true
                __text:"Kwota: "
                __hTextAlignment: Text.AlignHCenter
                width: 200
            }
            LineEditReadOnly{
                id:sumToPay
                anchors {
                    top:sumToPayLabel.top
                    left: sumToPayLabel.right
                    right: otherInvoiceData.right
                }
                height: 30
                width: 80
                text: "XXXXXX"
                __fontSize: 15
            }
        }

        Item {
            id: soldItemsRootItem
            anchors{
                top:otherInvoiceData.bottom
                left: otherInvoiceData.left
                right: invoiceDetailsRootItem.right
                bottom: invoiceDetailsRootItem.bottom
                topMargin: 2
            }

            FilledRectangleWithText{
                id: soldItemsLabel
                anchors {
                    top:soldItemsRootItem.top
                    left: soldItemsRootItem.left
                    right: soldItemsRootItem.right
                }
                height: 30
                __fontBold: true
                __text:"Pozycje na rachunku"
                __hTextAlignment: Text.AlignLeft
            }

            Component{
                id: lvInvoiceElem

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
                        width: 60
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
                        id:plantNameElem
                        text: model.buyerName
                        font.pixelSize: fontSize
                        font.bold: elemRootRec.__fontBold
                        color: __fontColor
                        font.family: __font
                        height: elemRootRec.height
                        width: elemRootRec.width *0.4
                        anchors{
                            top: elemRootRec.top
                            left: lpElem.right
                        }
                        background: InvElem_bck{}
                    }
                    TextField{
                        id:plantQuatityElem
                        text: model.adress
                        font.pixelSize: fontSize
                        font.bold: elemRootRec.__fontBold
                        color: __fontColor
                        font.family: __font
                        height: elemRootRec.height
                        width: elemRootRec.width *0.2
                        anchors{
                            top: elemRootRec.top
                            left: plantNameElem.right
                        }
                        background: InvElem_bck{}
                    }
                    TextField{
                        id:plantPriceElem
                        visible: true
                        text: model.town
                        height: elemRootRec.height
                        font.pixelSize: fontSize
                        font.bold: elemRootRec.__fontBold
                        color: __fontColor
                        font.family: __font
                        anchors{
                            top: elemRootRec.top
                            left: plantQuatityElem.right
                            right: rabatElem.left
                        }
                        background: InvElem_bck{}
                    }
                    TextField{
                        id:rabatElem
                        text: model.postalCode
                        font.pixelSize: fontSize
                        font.bold: elemRootRec.__fontBold
                        color: __fontColor
                        font.family: __font
                        height: elemRootRec.height
                        width: 120
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

                id: lvHeaderInvoiceElem

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
                        id:plantNameElem
                        visible: true
                        text: "Nazwa"
                        height: elemRootRec.height
                        color: __fontColor
                        horizontalAlignment:  "AlignHCenter"
                        font.bold: elemRootRec.__fontBold
                        font.pixelSize: fontSize
                        font.family: __font
                        width: elemRootRec.width *0.4
                        anchors{
                            top: elemRootRec.top
                            left: lpElem.right
                        }
                        background: InvHeaderElem_bck{}
                    }
                    TextField{
                        id:plantQuatityElem
                        text: "Ilość [szt.]"
                        font.pixelSize: fontSize
                        color: __fontColor
                        height: elemRootRec.height
                        horizontalAlignment:  "AlignHCenter"
                        font.bold: elemRootRec.__fontBold
                        font.family: __font
                        width: elemRootRec.width *0.2
                        anchors{
                            top: elemRootRec.top
                            left: plantNameElem.right
                        }
                        background: InvHeaderElem_bck{}
                    }
                    TextField{
                        id:plantPriceElem
                        text: "Cena [zł]"
                        font.pixelSize: fontSize
                        horizontalAlignment:  "AlignHCenter"
                        color: __fontColor
                        height: elemRootRec.height
                        font.bold: elemRootRec.__fontBold
                        font.family: __font
                        anchors{
                            top: elemRootRec.top
                            left: plantQuatityElem.right
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
                        width: 120
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
                id: lvDetails
                highlightMoveDuration: 0
                anchors{
                    right: soldItemsRootItem.right
                    left: soldItemsRootItem.left
                    top: soldItemsLabel.bottom
                    bottom: soldItemsRootItem.bottom
                    topMargin: 0
                }

                //                model: BuyersRecListModel{
                //                    mDatabase: myDatabase
                //                }

                delegate:lvInvoiceElem
                focus: true
                clip: true

                header:  lvHeaderInvoiceElem

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


        }
    }

}
