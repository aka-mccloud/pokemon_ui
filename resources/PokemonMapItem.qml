import QtQuick 2.0
import QtLocation 5.6

import TestModule 1.0

MapQuickItem {

    property Pokemon pokemon

    id: root
    scale: 0.6

    coordinate {
        latitude: pokemon.latitude
        longitude: pokemon.longitude
    }

    sourceItem: Rectangle {
        id: image
        width: 65
        height: 65
        clip: true
        color: "transparent"

        property int col: (pokemon.pokemon_id - 1) % numCols
        property int row: (pokemon.pokemon_id - 1) / numCols
        property int numCols: sprite.sourceSize.width / width
        property int numRows: sprite.sourceSize.height / height

        Image {
            id: sprite
            x: -parent.width * parent.col
            y: -parent.height * parent.row

            fillMode: Image.PreserveAspectCrop
            source: "sprites/icons-large-sprite.png"
            sourceSize.width: 455
            sourceSize.height: 1430
        }
    }

    anchorPoint.x: width / 2
    anchorPoint.y: height / 2

    MouseArea {
        cursorShape: Qt.PointingHandCursor
        anchors.fill: parent
        onClicked: {
            var encounter = pgoClient.encounter(pokemon);
            stackView.push("qrc:/CatchPokemonPage.qml", { encounter: encounter });
        }
    }
}
