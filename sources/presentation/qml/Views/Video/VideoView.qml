import QtQuick 2.6
import QtMultimedia 5.6

Rectangle {
    id: root

    property alias videoSource: videoOutput.source

    color: "black"

    VideoOutput {
        id: videoOutput
        anchors.fill: parent
    }
}
