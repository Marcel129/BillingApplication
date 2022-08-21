import QtQuick 2.0

Rectangle{
    id: rec1
    anchors{
        top: parent.top
        bottom: parent.bottom
        left: parent.left
    }
    gradient: Gradient{
        GradientStop{ position: 0.0; color:"#5865F2" }
        GradientStop{ position: 0.2; color:"lightgrey" }
        GradientStop{ position: 0.8; color:"lightgrey" }
        GradientStop{ position: 1.0; color:"#5865F2" }
    }
}

