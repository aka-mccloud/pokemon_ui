import QtQuick 2.5
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.0

import QtLocation 5.6

import TestModule 1.0

Window {
    visible: true
    width: 800
    height: 600

    TestObject {
        id: testObject
        onItemAppeared: function (pokemon) {
            var item = Qt.createComponent("PokemonMapItem.qml").createObject(map, { pokemon: pokemon });
            item.onClicked.connect(function (obj, mouse) {
                console.log(obj.pokemon.spawn_pint_id);
                console.log(obj.pokemon.encounter_id);
            });
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
                testObject.login(provider, login, password);
            }
        }
    }

    Plugin {
        id: mapbox
        preferred: ["mapbox"]
        PluginParameter { name: "mapbox.access_token"; value: "pk.eyJ1IjoibWNjbG91ZCIsImEiOiJjaXJ5azV1ZDUwMDBhMnVvdWRuY3NvZjc2In0.sxm3ylSJ5g_bW78tzbjnaA" }
        PluginParameter { name: "mapbox.map_id"; value: "mccloud.15673jfh" }
    }

    Map {
        id: map
        plugin: mapbox

        anchors.centerIn: parent
        anchors.fill: parent

        center {
            latitude: 50.4188908
            longitude: 30.5213649
        }

        zoomLevel: 15.0

        gesture.enabled: true
    }
}
