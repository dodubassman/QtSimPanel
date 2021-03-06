import QtQuick 2.6
import QtQuick.Window 2.2

Item {
    id: altimeter
    visible: true
    width: 256
    height: 256

    property real altitude: 0
    property real pressure: 29.1 // inHg


    Image {
        id: pressureLayer
        source: "../../assets/altimeter/pressure_cog.png"
        anchors.fill: parent
        rotation: -((pressure/0.02953-950)/120*360)
        Behavior on rotation {
            RotationAnimation { duration: 500; direction: RotationAnimation.Shortest }
        }

    }

    Image {
        id: feetsLayer
        source: "../../assets/altimeter/values_cog.png"
        anchors.fill: parent
    }

    Image {
        id: tenThousandFtLayer
        source: "../../assets/altimeter/10000ft_needle.png"
        anchors.fill: parent
        rotation: altitude/100000*360
        Behavior on rotation {
            RotationAnimation { duration: 500; direction: RotationAnimation.Shortest }
        }

    }


    Image {
        id: thousandFtLayer
        source: "../../assets/altimeter/1000ft_needle.png"
        anchors.fill: parent
        rotation: altitude/10000*360
        Behavior on rotation {
            RotationAnimation { duration: 500; direction: RotationAnimation.Shortest }
        }
    }

    Image {
        id: hundredFtLayer
        source: "../../assets/altimeter/100ft_needle.png"
        anchors.fill: parent
        rotation: altitude/1000*360
        Behavior on rotation {
            RotationAnimation { duration: 500; direction: RotationAnimation.Shortest }
        }
    }


}
