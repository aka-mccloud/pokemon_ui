import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0


Dialog {

    SystemPalette { id: palette }

    id: loginDialog
    modality: Qt.WindowModal
    title: "Login"
    width: 330
    height: 150

    property string login: ""
    property string password: ""
    property string provider: ""

    Binding { target: loginDialog; property: "login"; value: loginField.text }
    Binding { target: loginDialog; property: "password"; value: passwordField.text }
    Binding { target: loginDialog; property: "provider"; value: googleRadio.checked ? "google" : "ptc" }

    contentItem: Rectangle {
        color: palette.window
        GridLayout {
            id: gridLayout
            anchors.fill: parent
            Label {
                text: qsTr("Login:")
                Layout.row: 0
                Layout.column: 0
            }

            TextField {
                id: loginField
                Layout.fillWidth: true
                Layout.row: 0
                Layout.column: 1
            }

            Label {
                text: qsTr("Password:")
                Layout.row: 1
                Layout.column: 0
            }

            TextField {
                id: passwordField
                echoMode: TextInput.Password
                Layout.fillWidth: true
                Layout.row: 1
                Layout.column: 1
            }

            ExclusiveGroup {
                id: authProviderGroup
            }

            RadioButton {
                id: googleRadio
                text: qsTr("Google")
                checked: true
                Layout.row: 2
                Layout.columnSpan: 2
                exclusiveGroup: authProviderGroup
            }

            RadioButton {
                id: ptcRadio
                text: qsTr("Pokemon Trainer Club")
                Layout.row: 3
                Layout.columnSpan: 2
                exclusiveGroup: authProviderGroup
            }

            RowLayout {
                id: rowLayout1
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.row: 4
                Layout.columnSpan: 2

                Button {
                    id: button1
                    text: qsTr("Login")
                    onClicked: click(StandardButton.Ok);
                }

                Button {
                    id: button2
                    text: qsTr("Exit")
                    onClicked: click(StandardButton.Cancel);
                }
            }
        }
    }
}
