import QtQuick 2.5
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0
import QtQuick.Controls 1.4

import QtLocation 5.6

import TestModule 1.0

Window {
    id: root
    visible: true
    width: 800
    height: 600

    TestObject {
        id: pgoClient
        onItemAppeared: function (pokemon) {
            var item = Qt.createComponent("PokemonMapItem.qml").createObject(map, { pokemon: pokemon });
//            item.onClicked.connect(function (obj, mouse) {
//                console.log(obj.pokemon.spawn_pint_id);
//                console.log(obj.pokemon.encounter_id);
//                stackView.push("qrc:/CatchPokemonPage.qml", {})
//            });
            map.addMapItem(item);
        }

        onReady: {
            map.addMapItem(Qt.createComponent("MarkerMapItem.qml")
                           .createObject(map, { latitude: latitude, longitude: longitude }));
        }

        Component.onCompleted: {
            loginDialog.open();
        }

        state: "active"
    }

    LoginDialog {
        id: loginDialog

        onButtonClicked: {
            if (clickedButton === StandardButton.Ok) {
                pgoClient.login(provider, login, password);
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: MapPage {
            id: map
        }
    }
}
