import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

import TestModule 1.0

Item {

    property EncounterData encounter

    ToolBar {

        ToolButton {
            text: qsTr("Back")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: stackView.pop()
        }

        Label {
            id: pageTitle
            text: qsTr("Catch Pokemon")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    Label {
        text: encounter.status
    }
}
