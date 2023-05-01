import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Dialogs 1.3

import ProductsList 1.0

Item {
    id:rootItem
    anchors.fill: parent
    readonly property int __spacing: 25
    readonly property int __generalMargins: 15
    Item{
        id: mainInputData
        anchors{
            top:parent.top
            left:parent.left
            right:parent.right
        }
        height: 190
        Column{
            id:leftColumn
            anchors{
                top: mainInputData.top
                bottom: mainInputData.bottom
                left: mainInputData.left
                right: mainInputData.horizontalCenter
                margins : __generalMargins
                topMargin: 30
            }
            spacing: __spacing
            LineEdit{
                id:polishName
                caption: "Nazwa polska"
                anchors{
                    left: leftColumn.left
                    right: leftColumn.right
                }
            }
            LineEdit{
                id:species
                caption: "Gratunek"
                anchors{
                    left: leftColumn.left
                    right: leftColumn.right
                }
            }
        }

        Column{
            id:rightColumn
            anchors{
                top: mainInputData.top
                bottom: mainInputData.bottom
                left: mainInputData.horizontalCenter
                right: mainInputData.right
                margins : __generalMargins
                topMargin: 30
                leftMargin: 0
            }
            spacing: __spacing
            LineEdit{
                id: latinName
                caption: "Nazwa łacińska"
                anchors{
                    left: rightColumn.left
                    right: rightColumn.right
                }
            }
            ChooseField{
                id: typeName
                caption: "Rodzaj"
                anchors{
                    left: rightColumn.left
                    right: rightColumn.right
                }
                __model: myDatabase.getProductsTypes()
            }
        }

        MessageDialog {
            id:mmsgBox
            title: "Błąd"
            icon: StandardIcon.Warning
            text: "Uzupełnij brakujące pola"
            standardButtons: StandardButton.Ok
        }


        MButton {
            id:addButton
            anchors{
                bottom:parent.bottom
                right: parent.right
                margins: __generalMargins
            }
            text: "Dodaj"
            width: 80
            onClicked: {
                if(latinName.text == "" || polishName.text == "" || species.text == ""){
                    mmsgBox.visible = true
                }
                else{
                    myDatabase.addProduct(
                                typeName.__currentText,
                                latinName.text,
                                polishName.text,
                                species.text
                                )
                }


            }
        }
    }

    Item{
        id: searchRoot
        anchors{
            top: mainInputData.bottom
            left: rootItem.left
            right: rootItem.right
            margins: __generalMargins
        }
        height: searchElem.height

        LineEdit{
            id:searchElem
            caption: "Wyszukiwarka"
            anchors{
                top:searchRoot.top
                left: searchRoot.left
                right: searchButton.left
                rightMargin: __generalMargins
            }
        }
        MButton{
            id:searchButton
            text:"Szukaj"
            width: addButton.width
            anchors{
                top:searchRoot.top
                right: searchRoot.right
            }
        }
    }

    Item{
        id: listMainElem
        anchors{
            bottom: rootItem.bottom
            left:rootItem.left
            right:rootItem.right
            top: searchRoot.bottom
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
                    id:polishNameElem
                    text: model.polishName
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
                    id:latinNameElem
                    text: model.latinName
                    font.pixelSize: fontSize
                    font.bold: elemRootRec.__fontBold
                    color: __fontColor
                    font.family: __font
                    height: elemRootRec.height
                    width: elemRootRec.width *0.15
                    anchors{
                        top: elemRootRec.top
                        left: polishNameElem.right
                    }
                    background: InvElem_bck{}
                }
                TextField{
                    id:speciesElem
                    visible: true
                    text: model.species
                    height: elemRootRec.height
                    font.pixelSize: fontSize
                    font.bold: elemRootRec.__fontBold
                    color: __fontColor
                    font.family: __font
                    anchors{
                        top: elemRootRec.top
                        left: latinNameElem.right
                        right: typeElem.left
                    }
                    background: InvElem_bck{}
                }
                TextField{
                    id:typeElem
                    text: model.type
                    font.pixelSize: fontSize
                    font.bold: elemRootRec.__fontBold
                    color: __fontColor
                    font.family: __font
                    height: elemRootRec.height
                    width: elemRootRec.width *0.15
                    anchors{
                        top: elemRootRec.top
                        right: evidenceNumberElem.left
                    }
                    background: InvElem_bck{}
                }
                TextField{
                    id:evidenceNumberElem
                    text: model.evidenceNumber
                    font.pixelSize: fontSize
                    font.bold: elemRootRec.__fontBold
                    color: __fontColor
                    font.family: __font
                    height: elemRootRec.height
                    width: 140
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
                    id:polishNameElem
                    visible: true
                    text: "Nazwa polska"
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
                    id:latinNameElem
                    text: "Nazwa łacińska"
                    font.pixelSize: fontSize
                    color: __fontColor
                    height: elemRootRec.height
                    horizontalAlignment:  "AlignHCenter"
                    font.bold: elemRootRec.__fontBold
                    font.family: __font
                    width: elemRootRec.width *0.15
                    anchors{
                        top: elemRootRec.top
                        left: polishNameElem.right
                    }
                    background: InvHeaderElem_bck{}
                }
                TextField{
                    id:speciesElem
                    text: "Gatunek"
                    font.pixelSize: fontSize
                    horizontalAlignment:  "AlignHCenter"
                    color: __fontColor
                    height: elemRootRec.height
                    font.bold: elemRootRec.__fontBold
                    font.family: __font
                    anchors{
                        top: elemRootRec.top
                        left: latinNameElem.right
                        right: typeElem.left
                    }
                    background: InvHeaderElem_bck{}
                }
                TextField{
                    id:typeElem
                    text: "Rodzaj"
                    color: __fontColor
                    font.pixelSize: fontSize
                    horizontalAlignment:  "AlignHCenter"
                    font.family: __font
                    font.bold: elemRootRec.__fontBold
                    height: elemRootRec.height
                    width: elemRootRec.width *0.15
                    anchors{
                        top: elemRootRec.top
                        right: evidenceNumberElem.left
                    }
                    background: InvHeaderElem_bck{}
                }
                TextField{
                    id:evidenceNumberElem
                    text: "Nr. ewidencyjny"
                    color: __fontColor
                    font.pixelSize: fontSize
                    horizontalAlignment:  "AlignHCenter"
                    font.family: __font
                    font.bold: elemRootRec.__fontBold
                    height: elemRootRec.height
                    width: 140
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

            model: ProductRecListModel{
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
            width: addButton.width
            anchors{
                right: listMainElem.right
                top: listMainElem.top
                margins: __generalMargins
                topMargin: 10
            }
            onClicked: {
                myDatabase.removeProductAt(lv.currentIndex)
            }
        }
    }



}
