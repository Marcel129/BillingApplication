import QtQuick 2.2
import QtQuick.Controls 2.0

Component{
    id: lvHeaderElem

    Rectangle{
        readonly property ListView delegLv: ListView.view
        readonly property int fontSize: 15
        id: elemRootRec
        anchors{
            right: parent.right
            left: parent.left
        }
        implicitHeight: 30
        TextField{
            id:lpElem
            text: "Lp"
            color: "grey"
            height: elemRootRec.height
            width: 30
            font.pixelSize: fontSize
            anchors{
                top: elemRootRec.top
                left: elemRootRec.left
            }
        }
        TextField{
            id:nameElem
            visible: true
            text: "Nazwa"
            height: elemRootRec.height
            font.pixelSize: fontSize
            anchors{
                top: elemRootRec.top
                left: lpElem.right
                right: priceElem.left
            }
        }
        TextField{
            id:priceElem
            text: "Cena [zł]"
            font.pixelSize: fontSize
            height: elemRootRec.height
            width: 100
            anchors{
                top: elemRootRec.top
                right: ammountElem.left
            }
        }
        TextField{
            id:ammountElem
            text: "Ilość [szt.]"
            font.pixelSize: fontSize
            height: elemRootRec.height
            width: 100
            anchors{
                top: elemRootRec.top
                right: rabatElem.left
            }
        }
        TextField{
            id:rabatElem
            text: "Rabat [%]"
            font.pixelSize: fontSize
            height: elemRootRec.height
            width: 100
            anchors{
                top: elemRootRec.top
                right: elemRootRec.right
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
