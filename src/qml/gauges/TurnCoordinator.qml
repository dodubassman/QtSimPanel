import QtQuick 2.6
import QtQuick.Window 2.2

Item {
    id: turnCoordinator
    visible: true
    width: 256
    height: 256

    property int slipDeviation: 0
    property int roll: 0

    Image {
        id: background
        source: "../../assets/turn_coordinator/turnslip_disc.png"
        anchors.fill: parent
    }

    Image {
        id: slipBall
        source: "../../assets/turn_coordinator/ball.png"
        x: slipDeviation/100*60
        width: 256
        height: 256
        Behavior on x {
            NumberAnimation { duration: 500 }
        }
    }

    Image {
        id: background2
        source: "../../assets/turn_coordinator/turnslip.png"
        anchors.fill: parent
    }

    Image {
        id: aircraftLayer
        source: "../../assets/turn_coordinator/turnslip_planeshape.png"
        anchors.fill: parent
        rotation: roll
        Behavior on rotation {
            RotationAnimation { duration: 500; direction: RotationAnimation.Shortest }
        }
    }
}
