import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3

import BuyersList 1.0
import RecipersList 1.0

Item {
    anchors.fill: parent
    id:rootItem
    readonly property int __spacing: 25
    readonly property int __generalMargins: 15

    MessageDialog {
        id:mmsgBox
        title: "Błąd"
        icon: StandardIcon.Warning
        text: "Uzupełnij brakujące pola"
        standardButtons: StandardButton.Ok
    }

    MessageDialog {
        id: mmsgBoxOk
        title: "Informacja"
        text: "Poprawnie dodano pozycję do bazy"
        standardButtons: StandardButton.Ok
        onAccepted: {
            close()
        }
    }

    Item{
        id: creatingComponentsRoot
        anchors{
            top:parent.top
            left:parent.left
            right:parent.right
        }
        clip:true
        height: 300
        Column{
            id: leftColumn
            anchors{
                top: creatingComponentsRoot.top
                bottom: creatingComponentsRoot.bottom
                left: creatingComponentsRoot.left
                right: creatingComponentsRoot.horizontalCenter
                margins : __generalMargins
                topMargin: 30
            }
            spacing: __spacing
            LineEdit{
                id: buyerNameElem
                caption: "Nazwa"
                anchors{
                    left: leftColumn.left
                    right: leftColumn.right
                }
            }
            LineEdit{
                id: buyerAdressElem
                caption: "Adres"
                anchors{
                    left: leftColumn.left
                    right: leftColumn.right
                }
            }
            Row{
                id:adress2Row
                anchors{
                    left: leftColumn.left
                    right: leftColumn.right
                }
                height: buyerPC.height
                spacing: __spacing
                LineEdit{
                    id: buyerPC
                    width: (adress2Row.width - __spacing)/2
                    caption: "Kod pocztowy"
                    anchors{
                        top:adress2Row.top
                        bottom: adress2Row.bottom
                    }
                }
                LineEdit{
                    id: buyerTown
                    caption: "Miasto"
                    width: (adress2Row.width - __spacing)/2
                    anchors{
                        top:adress2Row.top
                        bottom: adress2Row.bottom
                    }
                }
            }
            LineEdit{
                id: buyerNIP
                caption: "NIP"
                anchors{
                    left: leftColumn.left
                    right: leftColumn.right
                }
            }

        }
        MButton {
            id:addBuyerButton
            anchors{
                bottom:creatingComponentsRoot.bottom
                right: leftColumn.right
            }
            text: "Dodaj nabywcę"
            width: 160
            onClicked: {
                if(buyerNameElem.text == "" ||
                        buyerAdressElem.text == "" ||
                        buyerPC.text == "" ||
                        buyerTown.text == "" ||
                        buyerNIP.text == "" ){
                    mmsgBox.visible = true
                }
                else{
                    myDatabase.addCustomer(
                                buyerNameElem.text,
                                buyerAdressElem.text,
                                buyerTown.text,
                                buyerPC.text,
                                buyerNIP.text
                                );
                    mmsgBoxOk.open()
                    buyerNameElem.text = ""
                    buyerAdressElem.text = ""
                    buyerTown.text = ""
                    buyerPC.text = ""
                    buyerNIP.text = ""
                    buyerNameForRecip.__model = myDatabase.getCustomersNames()

                }
            }
        }

        Column{
            id:rightColumn
            anchors{
                top: creatingComponentsRoot.top
                bottom: creatingComponentsRoot.bottom
                left: creatingComponentsRoot.horizontalCenter
                right: creatingComponentsRoot.right
                margins : __generalMargins
                topMargin: 30
                leftMargin: 0
            }
            spacing: __spacing

            ChooseField{
                id: buyerNameForRecip
                caption: "Nabywca"
                anchors{
                    left: rightColumn.left
                    right: rightColumn.right
                }
                __model: myDatabase.getCustomersNames()
            }
            LineEdit{
                id: recipName
                caption: "Nazwa"
                anchors{
                    left: rightColumn.left
                    right: rightColumn.right
                }
            }
            LineEdit{
                id: recipAdress
                caption: "Adres"
                anchors{
                    left: rightColumn.left
                    right: rightColumn.right
                }
            }
            Row{
                id:adress2RowRecip
                anchors{
                    left: rightColumn.left
                    right: rightColumn.right
                }
                height: buyerPC.height
                spacing: __spacing
                LineEdit{
                    id: recipPC
                    width: (adress2RowRecip.width - __spacing)/2
                    caption: "Kod pocztowy"
                    anchors{
                        top:adress2RowRecip.top
                        bottom: adress2RowRecip.bottom
                    }
                }
                LineEdit{
                    id: recipTown
                    caption: "Miasto"
                    width: (adress2RowRecip.width - __spacing)/2
                    anchors{
                        top:adress2RowRecip.top
                        bottom: adress2RowRecip.bottom
                    }
                }
            }
        }
        MButton {
            id:addRecipButton
            anchors{
                bottom:creatingComponentsRoot.bottom
                right: rightColumn.right
            }
            text: "Dodaj odbiorcę"
            width: 160

            onClicked: {
                if(recipName.text == "" ||
                        recipAdress.text == "" ||
                        recipTown.text == "" ||
                        recipPC.text == "" ){
                    mmsgBox.visible = true
                }
                else{
                    myDatabase.addReciper(
                                buyerNameForRecip.__currentText,
                                recipName.text,
                                recipAdress.text,
                                recipTown.text,
                                recipPC.text,
                                );
                    mmsgBoxOk.open()
                    recipName.text = ""
                    recipAdress.text = ""
                    recipTown.text = ""
                    recipPC.text = ""
                }
            }
        }

}

    Item{
        id:listsRootItem
        anchors{
            bottom:rootItem.bottom
            right: rootItem.right
            left:rootItem.left
            top:creatingComponentsRoot.bottom
            margins: __generalMargins
        }

        MButton{
            id: removePositionButton
            text: "Usuń"
            width: 80
            anchors{
                right: listsRootItem.right
                top: listsRootItem.top
            }
            onClicked: {
                messageDialogDelete.open()
            }
        }

        MessageDialog {
            id: messageDialogDelete
            title: "Ostrzeżenie"
            text: "Czy na pewno chcesz usunąć pozycję z bazy? Ta decyzja jest nieodwracalna"
            standardButtons: StandardButton.Yes | StandardButton.No
            onYes: {
                myDatabase.removeCustomerAt(lv.currentIndex)
                //refresh the buyers list
                buyerNameForRecip.__model = myDatabase.getCustomersNames()
                close()
            }
            onNo:{
                close()
            }
        }

        Item{
            id:  buyersListMainElem
            anchors{
                right:removePositionButton.left
                left: listsRootItem.left
                top: listsRootItem.top
                rightMargin: 10
            }
            height: 300

            Component{
                id: lvBuyerElem

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
                        id:buyerNameElem
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
                        id:buyerAdressElem
                        text: model.adress
                        font.pixelSize: fontSize
                        font.bold: elemRootRec.__fontBold
                        color: __fontColor
                        font.family: __font
                        height: elemRootRec.height
                        width: elemRootRec.width *0.2
                        anchors{
                            top: elemRootRec.top
                            left: buyerNameElem.right
                        }
                        background: InvElem_bck{}
                    }
                    TextField{
                        id:townElem
                        visible: true
                        text: model.town
                        height: elemRootRec.height
                        font.pixelSize: fontSize
                        font.bold: elemRootRec.__fontBold
                        color: __fontColor
                        font.family: __font
                        anchors{
                            top: elemRootRec.top
                            left: buyerAdressElem.right
                            right: postalCodeElem.left
                        }
                        background: InvElem_bck{}
                    }
                    TextField{
                        id:postalCodeElem
                        text: model.postalCode
                        font.pixelSize: fontSize
                        font.bold: elemRootRec.__fontBold
                        color: __fontColor
                        font.family: __font
                        height: elemRootRec.height
                        width: 120
                        anchors{
                            top: elemRootRec.top
                            right: nipElem.left
                        }
                        background: InvElem_bck{}
                    }
                    TextField{
                        id:nipElem
                        text: model.nip
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
                        id:buyerNameElem
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
                        id:buyerAdressElem
                        text: "Adres"
                        font.pixelSize: fontSize
                        color: __fontColor
                        height: elemRootRec.height
                        horizontalAlignment:  "AlignHCenter"
                        font.bold: elemRootRec.__fontBold
                        font.family: __font
                        width: elemRootRec.width *0.2
                        anchors{
                            top: elemRootRec.top
                            left: buyerNameElem.right
                        }
                        background: InvHeaderElem_bck{}
                    }
                    TextField{
                        id:townElem
                        text: "Miasto"
                        font.pixelSize: fontSize
                        horizontalAlignment:  "AlignHCenter"
                        color: __fontColor
                        height: elemRootRec.height
                        font.bold: elemRootRec.__fontBold
                        font.family: __font
                        anchors{
                            top: elemRootRec.top
                            left: buyerAdressElem.right
                            right: postalCodeElem.left
                        }
                        background: InvHeaderElem_bck{}
                    }
                    TextField{
                        id:postalCodeElem
                        text: "Kod pocztowy"
                        color: __fontColor
                        font.pixelSize: fontSize
                        horizontalAlignment:  "AlignHCenter"
                        font.family: __font
                        font.bold: elemRootRec.__fontBold
                        height: elemRootRec.height
                        width: 120
                        anchors{
                            top: elemRootRec.top
                            right: nipElem.left
                        }
                        background: InvHeaderElem_bck{}
                    }
                    TextField{
                        id:nipElem
                        text: "NIP"
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
                id: lv
                highlightMoveDuration: 0
                anchors{
                    right: buyersListMainElem.right
                    left: buyersListMainElem.left
                    top: buyersListMainElem.top
                    bottom: buyersListMainElem.bottom
                    topMargin: 0
                }

                model: BuyersRecListModel{
                    mDatabase: myDatabase
                }

                delegate:lvBuyerElem
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
                onCurrentIndexChanged:  {
                    myDatabase.refreshRecipersTableView(lv.currentIndex)

                }

            }
        }


        MButton{
            id: removeReciperPositionButton
            text: "Usuń"
            width: removePositionButton.width
            anchors{
                right: listsRootItem.right
                top: recipersListMainElem.top
            }
            onClicked: {
                messageDialogDeleteReciper.open()
            }
        }

        MessageDialog {
            id: messageDialogDeleteReciper
            title: "Ostrzeżenie"
            text: "Czy na pewno chcesz usunąć pozycję z bazy? Ta decyzja jest nieodwracalna"
            standardButtons: StandardButton.Yes | StandardButton.No
            onYes: {
                myDatabase.removeReciperAt(lv.currentIndex, lvRecipers.currentIndex)
                //refresh the buyers list
                buyerNameForRecip.__model = myDatabase.getCustomersNames()
                close()
            }
            onNo:{
                close()
            }
        }

        Item{
            id:  recipersListMainElem
            anchors{
                right:removePositionButton.left
                left: listsRootItem.left
                top: buyersListMainElem.bottom
                bottom: listsRootItem.bottom
                rightMargin: 10
                topMargin: 20
            }

            Component{
                id: lvReciperElem

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
                        id:reciperNameElem
                        text: model.reciperName
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
                        id:reciperAdressElem
                        text: model.address
                        font.pixelSize: fontSize
                        font.bold: elemRootRec.__fontBold
                        color: __fontColor
                        font.family: __font
                        height: elemRootRec.height
                        width: elemRootRec.width *0.25
                        anchors{
                            top: elemRootRec.top
                            left: reciperNameElem.right
                        }
                        background: InvElem_bck{}
                    }
                    TextField{
                        id:townElem
                        visible: true
                        text: model.town
                        height: elemRootRec.height
                        font.pixelSize: fontSize
                        font.bold: elemRootRec.__fontBold
                        color: __fontColor
                        font.family: __font
                        anchors{
                            top: elemRootRec.top
                            left: reciperAdressElem.right
                            right: postalCodeElem.left
                        }
                        background: InvElem_bck{}
                    }
                    TextField{
                        id:postalCodeElem
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

                id: lvHeaderReciperElem

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
                        id:buyerNameElem
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
                        id:buyerAdressElem
                        text: "Adres"
                        font.pixelSize: fontSize
                        color: __fontColor
                        height: elemRootRec.height
                        horizontalAlignment:  "AlignHCenter"
                        font.bold: elemRootRec.__fontBold
                        font.family: __font
                        width: elemRootRec.width *0.25
                        anchors{
                            top: elemRootRec.top
                            left: buyerNameElem.right
                        }
                        background: InvHeaderElem_bck{}
                    }
                    TextField{
                        id:townElem
                        text: "Miasto"
                        font.pixelSize: fontSize
                        horizontalAlignment:  "AlignHCenter"
                        color: __fontColor
                        height: elemRootRec.height
                        font.bold: elemRootRec.__fontBold
                        font.family: __font
                        anchors{
                            top: elemRootRec.top
                            left: buyerAdressElem.right
                            right: postalCodeElem.left
                        }
                        background: InvHeaderElem_bck{}
                    }
                    TextField{
                        id:postalCodeElem
                        text: "Kod pocztowy"
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
                id: lvRecipers
                highlightMoveDuration: 0
                anchors{
                    right: recipersListMainElem.right
                    left: recipersListMainElem.left
                    top: recipersListMainElem.top
                    bottom: recipersListMainElem.bottom
                    topMargin: 0
                }

                model: ReciperRecListModel{
                    mDatabase: myDatabase
                }

                delegate:lvReciperElem
                focus: true
                clip: true

                header:  lvHeaderReciperElem

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


