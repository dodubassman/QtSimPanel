import QtQuick 2.6
import QtQuick.Window 2.2

Item {
    id: turnCoordinator
    visible: true
    width: 256
    height: 256

    property int slipDeviation: 0
    property int turnRoll: 0

    onTurnRollChanged: {
        aircraftLayer.rotation = turnRoll > 60 ? 60 : turnRoll;
    }

    onSlipDeviationChanged: {
        var rotation = slipDeviation/100*12
        slipLayer.rotation = rotation
        slipBall.rotation = - rotation
    }

    Image {
        id: background
        source: "../../assets/turn_coordinator/background.svg"
        anchors.fill: parent
    }

    Item {
        id: slipLayer
        width: 31;
        anchors.bottom: background.bottom
        anchors.top: background.top
        anchors.topMargin: -150
        anchors.horizontalCenter: background.horizontalCenter
        anchors.bottomMargin: 45
        transformOrigin: Item.Top
        Behavior on rotation {
            RotationAnimation { duration: 500; direction: RotationAnimation.Shortest }
        }
        Image {
            id: slipBall
            anchors.bottom: slipLayer.bottom
            width: 31; height: 48
            source: "../../assets/turn_coordinator/slip_indicator.svg"
            Behavior on rotation {
            RotationAnimation { duration: 500; direction: RotationAnimation.Shortest }
        }
        }
    }

    Image {
        id: background2
        source: "../../assets/turn_coordinator/background2.svg"
        anchors.fill: parent
    }

    Image {
        id: aircraftLayer
        source: "../../assets/turn_coordinator/aircraft.svg"
        anchors.fill: parent
        Behavior on rotation {
            RotationAnimation { duration: 500; direction: RotationAnimation.Shortest }
        }

    }

    Image {
        id: flagLayer
        visible: false
        source: "../../assets/turn_coordinator/flag.svg"
        anchors.fill: parent
    }
}
