import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    title: qsTr("TableViewDemo")
    width: 640
    height: 480
    visible: true
    id: applicationWindow
    property bool sortEnabled

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
        Menu {
            title: qsTr("&Settings")
            ExclusiveGroup {
                id: sortGroup
            }
            MenuItem {
                text: qsTr("E&nable Sort")
                exclusiveGroup: sortGroup
                checkable: true
                checked: sortEnabled
                onToggled: {
                    sortEnabled = checked;
                }
            }
            MenuItem {
                text: qsTr("D&isable Sort")
                exclusiveGroup: sortGroup
                checkable: true
                checked: !sortEnabled
            }
        }
    }

    RowLayout {
        anchors.fill: parent

        QmlListModelTableView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            sortEnabled: applicationWindow.sortEnabled
        }
        QAbstractListModelTableView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            sortEnabled: applicationWindow.sortEnabled
        }
    }
}
