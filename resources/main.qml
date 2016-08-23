import QtQuick 2.5

import QtLocation 5.6
import QtPositioning 5.6

import TestModule 1.0

Rectangle {
    visible: true
    anchors.fill: parent

    TestObject {
        id: testObject
        onItemAppeared: function (pokemon) {
            var item = Qt.createComponent("PokemonMapItem.qml").createObject(map, { pokemon: pokemon });
            item.onClicked.connect(function (obj, mouse) {
                console.log(obj);
            });
            map.addMapItem(item);
        }

//        state: "active"
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
