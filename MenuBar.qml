import QtQuick 2.0

Rectangle{
    id: rec1
    border.color: "darkgreen"
    border.width: 2
    anchors{
        top: parent.top
        bottom: parent.bottom
        left: parent.left
    }
    gradient: Gradient{
        GradientStop{ position: 0.0; color:"green" }
        GradientStop{ position: 0.2; color:"grey" }
        GradientStop{ position: 0.8; color:"grey" }
        GradientStop{ position: 1.0; color:"green" }
    }
//    BarButton{
//        id: bb1
//        y: parent.height/6 + ( bb1.height + 10)*0
//        text: "Faktura"

//    }
//    BarButton{
//        id: bb2
//        y: parent.height/6 + ( bb1.height + 10)*1
//        text: "Kontrahenci"
//    }
//    BarButton{
//        id: bb3
//        y: parent.height/6 + ( bb1.height + 10)*2
//        text: "Baza roślin"
//    }
}

