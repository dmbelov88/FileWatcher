import QtQuick 2.5
import QtQuick.Layouts 1.3

Rectangle {
    anchors.fill: parent

    ColumnLayout {
        anchors.fill: parent
        spacing: 20

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "hello world"
        }

        Custom {
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}
