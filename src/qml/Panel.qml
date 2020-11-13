import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import "gauges"


Item {

    width: 800
    height: 600

    Altimeter {
        id: altimeter
        altitude: 0
        pressure: 1013
    }

    VerticalSpeed {
        x: 260
        id: verticalspeed
        rate: 0
    }

    Airspeed {
        x: 520
        id: airspeed
        tas: 0
    }

    TurnCoordinator {
        id: turnCoordinator
        x: 780
        turnRoll: 60
        slipDeviation: 0
    }


    Button {
        text: "Randomize"
        anchors.bottom: parent.bottom
        onClicked: {
            altimeter.altitude = Math.floor(Math.random()*50000)
            altimeter.pressure = 950
            verticalspeed.rate = Math.floor(Math.random()*4000 - 2000)
            airspeed.tas = Math.floor(Math.random()*200)
            turnCoordinator.slipDeviation = Math.floor(Math.random()*200 - 100)
            turnCoordinator.turnRoll = Math.floor(Math.random()*120 - 60)

        }

    }
}
