import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.qmlmodels
import QtQuick.Layouts 2.5

Page {
    id: homePage
    title: qsTr("Rachunek")

    ColumnLayout {
        id: columnLayout_main
        anchors.fill: parent
        anchors.margins: 5

        GridLayout {
            id: gridLayout_main
            Layout.alignment: Qt.AlignVCenter

            //        anchors.bottomMargin: homePage.height * 0.6
            columns: 2

            ColumnLayout {
                id: columnLayout
                Layout.column: 0
                Layout.row: 0

                Label {
                    text: "Sprzedawca:"
                }
                ComboBox {
                    Layout.fillWidth: true
                }
            }
            ColumnLayout {
                id: columnLayout1
                Layout.column: 0
                Layout.row: 1
                Label {
                    text: "Nabywca:"
                }
                ComboBox {
                    Layout.fillWidth: true
                }
            }
            ColumnLayout {
                id: columnLayout2
                Layout.column: 0
                Layout.row: 2
                Label {
                    text: "Odbiorca:"
                }
                ComboBox {
                    Layout.fillWidth: true
                    displayText: "asdfghg"
                }
            }
            ColumnLayout {
                id: columnLayout3
                Layout.column: 0
                Layout.row: 3
                Label {
                    text: "Sposób płatności:"
                }
                ComboBox {
                    id: comboBox_paymentMethod
                    Layout.fillWidth: true
                }
            }
            ColumnLayout {
                id: columnLayout4
                Layout.column: 1
                Layout.row: 2
                Label {
                    text: "Miejsce wystawienia"
                }
                TextField {
                    //                Layout.fillWidth: true
                    implicitWidth: homePage.width * 0.5
                }
            }
            ColumnLayout {
                id: columnLayout5
                Layout.column: 1
                Layout.row: 3
                Label {
                    text: "Sposób płatności:"
                }
                RowLayout {
                    id: rowLayout
                    Switch {
                        id: switch1
                    }
                    TextField {
                        //                    Layout.fillWidth: true
                        implicitWidth: homePage.width * 0.5 - switch1.width - 5
                    }
                }
            }
        }

        GridLayout {
            id: gridLayout_bottom
            //            Layout.fillWidth: true
            //            anchors.margins: 5
            //            anchors.topMargin: 0.65 * homePage.height
            columns: 2

            ComboBox {
                Layout.fillWidth: true
            }

            Button {
                id: button1
                text: "Dodaj"
            }

            TableView {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.row: 1
                clip: true
                Layout.column: 0

                columnSpacing: 0
                rowSpacing: 1
                boundsBehavior: Flickable.StopAtBounds

                model: TableModel {
                    TableModelColumn {
                        display: "checked"
                    }
                    TableModelColumn {
                        display: "amount"
                    }
                    TableModelColumn {
                        display: "fruitType"
                    }
                    TableModelColumn {
                        display: "fruitName"
                    }

                    // Each row is one type of fruit that can be ordered
                    rows: [{
                            "checked"// Each property is one cell/column.
                            : false,
                            "amount": 1,
                            "fruitType": "Apple",
                            "fruitName": "Granny Smith"
                        }, {
                            "checked": true,
                            "amount": 4,
                            "fruitType": "Orange",
                            "fruitName": "Navel"
                        }, {
                            "checked": false,
                            "amount": 1,
                            "fruitType": "Banana",
                            "fruitName": "Cavendish"
                        }]
                }
                delegate: DelegateChooser {

                    DelegateChoice {
                        column: 0
                        delegate: CheckBox {
                            checked: model.display
                            onToggled: model.display = checked
                        }
                    }
                    DelegateChoice {
                        column: 1
                        delegate: SpinBox {
                            value: model.display
                            onValueModified: model.display = value
                        }
                    }
                    DelegateChoice {
                        column: 2
                        delegate: TextField {
                            selectByMouse: true
                            implicitWidth: 60
                        }
                    }
                    DelegateChoice {
                        delegate: TextField {
                            text: model.display
                            selectByMouse: true
                            Layout.fillWidth: true
                            onAccepted: model.display = text
                        }
                    }
                }
            }
            Button {
                id: button2
                text: "Usuń"
                Layout.row: 1
                Layout.column: 1
                Layout.alignment: Qt.AlignTop
            }
            Button {
                id: button3
                text: "Utwórz"
                Layout.row: 2
                Layout.column: 1
                onPressed: f.createFV()
                Layout.alignment: Qt.AlignBottom | Qt.AlignRight
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:1.25;height:480;width:640}
}
##^##*/

