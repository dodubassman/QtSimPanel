import QtQuick 2.6
import QtQuick.Window 2.2

Item {
    id: turnCoordinator
    visible: true
    width: 256
    height: 256

    property real pitch: 0
    property real roll: 0

    Item {
        id: rollLayer
        anchors.fill: parent
        rotation: - roll

        Behavior on rotation {
            RotationAnimation { duration: 500; direction: RotationAnimation.Shortest }
        }

        Image {
            id: background
            source: "../../assets/artificial_horizon/background.png"
            anchors.fill: parent
        }

        Image {
            id: pitchScale
            source: "../../assets/artificial_horizon/pitchscale.png"
            width: 256
            height: 256
            y: pitch
            Behavior on y {
                NumberAnimation { duration: 500 }
            }
        }

        Image {
            id: rolldial
            source: "../../assets/artificial_horizon/rolldial.png"
            anchors.fill: parent
        }
    }

    Image {
        id: foreground
        source: "../../assets/artificial_horizon/foreground.png"
        anchors.fill: parent
    }

}
