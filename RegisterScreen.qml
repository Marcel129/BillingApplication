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
            bottom: rootItem.bottom
            left:rootItem.left
            right:rootItem.right
            top: rootItem.top
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
}
