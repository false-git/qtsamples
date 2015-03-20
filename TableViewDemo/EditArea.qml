import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ColumnLayout {
    property alias numberValue: numberSpin.value
    property alias nameValue: nameText.text
    property alias ageValue: ageSpin.value
    property bool selected: false
    signal addRow()
    signal updateRow()
    signal deleteRow()
    RowLayout {
        Label {
            text: qsTr("No.")
        }
        SpinBox {
            id: numberSpin
            minimumValue: 1
            maximumValue: 999
        }
        Label {
            text: qsTr("Name")
        }
        TextField {
            id: nameText
        }
        Label {
            text: qsTr("Age")
        }
        SpinBox {
            id: ageSpin
            minimumValue: 0
            maximumValue: 99
        }
    }
    RowLayout {
        Button {
            text: qsTr("Add")
            onClicked: addRow()
        }
        Button {
            text: qsTr("Update")
            onClicked: updateRow()
            visible: selected
        }
        Button {
            text: qsTr("Delete")
            onClicked: deleteRow()
            visible: selected
        }
    }
}

