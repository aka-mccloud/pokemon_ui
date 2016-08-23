import QtQuick 2.0
import QtLocation 5.6

MapQuickItem {

    property double latitude: 0.0
    property double longitude: 0.0

    coordinate {
        latitude: latitude
        longitude: longitude
    }

    sourceItem: Image {
        id: image
        fillMode: Image.PreserveAspectCrop
        source: "sprites/marker-icon.png"
    }

    anchorPoint.x: image.width/2
    anchorPoint.y: image.height

    MouseArea {
        cursorShape: Qt.PointingHandCursor

        anchors.fill: parent
        drag.target: parent
//        drag.drop: {
//            // do something
//        }
    }
}
