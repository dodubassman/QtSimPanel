import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import "gauges"


Item {

    width: 800
    height: 600


    Airspeed {
        id: airspeed
        tas: 0
    }


    ArtificialHorizon {
        id: artificialHorizon
        x: 285
        roll: qSimPanel.flightData.roll
        pitch: qSimPanel.flightData.pitch
    }

    Altimeter {
        id: altimeter
        x: 570
    }

    TurnCoordinator {
        id: turnCoordinator
        y: 302
        roll: qSimPanel.flightData.roll
    }


    HeadingIndicator {
        id: headingIndicator
        x: 285
        y: 302
        heading: qSimPanel.flightData.heading
    }


    VerticalSpeed {
        id: verticalspeed
        x: 570
        y: 302
        rate: 0
    }







    Button {
        text: "Randomize"
        anchors.bottom: parent.bottom
        onClicked: {
            altimeter.altitude = Math.floor(Math.random()*50000)
            altimeter.pressure = Math.floor(Math.random()*(1050-946)+946)

            verticalspeed.rate = Math.floor(Math.random()*4000 - 2000)
            airspeed.tas = Math.floor(Math.random()*200)
            turnCoordinator.slipDeviation = Math.floor(Math.random()*200 - 100)

            var roll = Math.floor(Math.random()*120 - 60)
            turnCoordinator.roll = roll
            artificialHorizon.roll = roll
            artificialHorizon.pitch = Math.random()*90 - 45

            headingIndicator.heading = Math.floor(Math.random()*360)
        }

    }
}
