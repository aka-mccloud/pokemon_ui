import QtQuick 2.0
import QtLocation 5.6

Map {
    plugin: Plugin {
        preferred: ["mapbox"]
        PluginParameter { name: "mapbox.access_token"; value: "pk.eyJ1IjoibWNjbG91ZCIsImEiOiJjaXJ5azV1ZDUwMDBhMnVvdWRuY3NvZjc2In0.sxm3ylSJ5g_bW78tzbjnaA" }
        PluginParameter { name: "mapbox.map_id"; value: "mccloud.15673jfh" }
    }

    center {
        latitude: 50.4188908
        longitude: 30.5213649
    }

    zoomLevel: 15.0

    gesture.enabled: true
}

