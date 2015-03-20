import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ColumnLayout {
    property bool sortEnabled;
    onSortEnabledChanged: {
        if (sortEnabled) {
            qmlModel.quick_sort()
        }
    }

    ListModel {
        id: qmlModel
        ListElement {
            number: 1
            name: "mike"
            age: 33
        }
        ListElement {
            number: 2
            name: "bob"
            age: 12
        }
        ListElement {
            number: 3
            name: "alice"
            age: 45
        }

        // 以下、http://qt-project.org/forums/viewthread/11108
        // の remy67 さんのコメントにあるSortListModelより。
        // ListModel をrootとするqmlファイルを作成すると、ListElementが中に配置できなくなるため、
        // ここに直書きする。
        // また、オリジナルはAscendingしか対応していなかったので、sort orderに対応させた。
        property string sortColumnName: "number"
        property bool sortOrderAscending: true
        function swap(a,b) {
            if (a<b) {
                move(a,b,1);
                move (b-1,a,1);
            }
            else if (a>b) {
                move(b,a,1);
                move (a-1,b,1);
            }
        }

        function partition(begin, end, pivot)
        {
            var piv=get(pivot)[sortColumnName];
            swap(pivot, end-1);
            var store=begin;
            var ix;
            for(ix=begin; ix<end-1; ++ix) {
                if (sortOrderAscending) {
                    if(get(ix)[sortColumnName] < piv) {
                        swap(store,ix);
                        ++store;
                    }
                } else {
                    if(get(ix)[sortColumnName] > piv) {
                        swap(store,ix);
                        ++store;
                    }
                }
            }
            swap(end-1, store);

            return store;
        }

        function qsort(begin, end)
        {
            if(end-1>begin) {
                var pivot=begin+Math.floor(Math.random()*(end-begin));

                pivot=partition( begin, end, pivot);

                qsort(begin, pivot);
                qsort(pivot+1, end);
            }
        }

        function quick_sort() {
            qsort(0,count)
        }
    }

    Text {
        text: "QML ListModel version"
    }

    TableView {
        id: tableView
        model: qmlModel
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
        onSortIndicatorColumnChanged: {
            qmlModel.sortColumnName = getColumn(sortIndicatorColumn).role
            qmlModel.quick_sort()
        }
        onSortIndicatorOrderChanged: {
            qmlModel.sortOrderAscending = (sortIndicatorOrder == Qt.AscendingOrder);
            qmlModel.quick_sort()
        }

        function appendRow(numberValue, nameValue, ageValue) {
            var data = {
                number: numberValue,
                name: nameValue,
                age: ageValue
            }
            model.append(data)
        }
        function updateRow(numberValue, nameValue, ageValue) {
            model.setProperty(currentRow, "number", numberValue);
            model.setProperty(currentRow, "name", nameValue);
            model.setProperty(currentRow, "age", ageValue);
        }
        function deleteRow() {
            model.remove(currentRow)
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

