import QtQuick 2.6
import QtQuick.Window 2.2

Item {
    id: altimeter
    visible: true
    width: 256
    height: 256

    property int altitude: 0
    property int pressure: 1013

    onAltitudeChanged: {
        tenThousandFtLayer.rotation = altitude/100000*360;
        thousandFtLayer.rotation = altitude/10000*360;
        hundredFtLayer.rotation = altitude/1000*360;
        pressureLayer.rotation = -((pressure-950)/120*360)
    }


    Image {
        id: pressureLayer
        source: "../../assets/altimeter/pressure_cog.svg"
        anchors.fill: parent
        Behavior on rotation {
            RotationAnimation { duration: 500; direction: RotationAnimation.Shortest }
        }

    }

    Image {
        id: feetsLayer
        source: "../../assets/altimeter/values_cog.svg"
        anchors.fill: parent
    }

    Image {
        id: tenThousandFtLayer
        source: "../../assets/altimeter/10000ft_needle.svg"
        anchors.fill: parent
        Behavior on rotation {
            RotationAnimation { duration: 500; direction: RotationAnimation.Shortest }
        }

    }


    Image {
        id: thousandFtLayer
        source: "../../assets/altimeter/1000ft_needle.svg"
        anchors.fill: parent
        Behavior on rotation {
            RotationAnimation { duration: 500; direction: RotationAnimation.Shortest }
        }
    }

    Image {
        id: hundredFtLayer
        source: "../../assets/altimeter/100ft_needle.svg"
        anchors.fill: parent
        Behavior on rotation {
            RotationAnimation { duration: 500; direction: RotationAnimation.Shortest }
        }
    }


}
