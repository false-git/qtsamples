import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

import PersonListModel 1.0

ColumnLayout {
    property alias sortEnabled: cppModel.sortEnabled
    PersonListModel {
        id: cppModel
        sortOrder: tableView.sortIndicatorOrder
        sortRole: tableView.getColumn(tableView.sortIndicatorColumn).role
    }

    Text {
        text: "C++ QAbstractListModel version"
    }

    TableView {
        id: tableView
        model: cppModel
        sortIndicatorVisible: sortEnabled;
        Layout.fillWidth: true
        Layout.fillHeight: true
        TableViewColumn {
            title: qsTr("No.")
            role: "number"
            width: 50
        }
        TableViewColumn {
            title: qsTr("Name")
            role: "name"
            width: 100
        }
        TableViewColumn {
            title: qsTr("Age")
            role: "age"
            width: 50
        }
        onCurrentRowChanged: {
            if (currentRow !== -1) {
                var data = model.get(currentRow)
                qmlEdit.numberValue = data.number
                qmlEdit.nameValue = data.name
                qmlEdit.ageValue = data.age
            }
        }
        function appendRow(numberValue, nameValue, ageValue) {
            model.appendRow(numberValue, nameValue, ageValue)
        }
        function updateRow(numberValue, nameValue, ageValue) {
            model.updateRow(currentRow, numberValue, nameValue, ageValue)
        }
        function deleteRow() {
            model.removeRow(currentRow)
            currentRow = -1
            selection.clear()
        }
    }
    EditArea {
        id: qmlEdit
        selected: tableView.currentRow !== -1
        onAddRow: {
            tableView.appendRow(numberValue, nameValue, ageValue)
        }
        onUpdateRow: {
            tableView.updateRow(numberValue, nameValue, ageValue)
        }
        onDeleteRow: {
            tableView.deleteRow()
        }
    }
}

