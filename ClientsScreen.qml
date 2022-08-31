import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.3

Item {
    anchors.fill: parent
    readonly property int __spacing: 25
    readonly property int __generalMargins: 15

    MessageDialog {
        id:mmsgBox
        title: "Błąd"
        icon: StandardIcon.Warning
        text: "Uzupełnij brakujące pola"
        standardButtons: StandardButton.Ok
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
                id: buyerName
                caption: "Nazwa"
                anchors{
                    left: leftColumn.left
                    right: leftColumn.right
                }
            }
            LineEdit{
                id: buyerAdress
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
                if(buyerName.text == "" ||
                        buyerAdress.text == "" ||
                        buyerPC.text == "" ||
                        buyerTown.text == "" ||
                        buyerNIP.text == "" ){
                    mmsgBox.visible = true
                }
                else{
                    myDatabase.addCustomer(
                                buyerName.text,
                                buyerAdress.text,
                                buyerTown.text,
                                buyerPC.text,
                                buyerNIP.text
                                );
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
                }
            }
        }
    }

}


