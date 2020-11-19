import QtQuick 2.6
import QtQuick.Window 2.2

Item {
    id: headingIndicator
    visible: true
    width: 256
    height: 256

    property real heading: 360

    Image {
        id: headingCog
        source: "../../assets/heading_indicator/dg_disc.png"
        anchors.fill: parent
        rotation: -heading
        Behavior on rotation {
            RotationAnimation { duration: 500; direction: RotationAnimation.Shortest }
        }

    }

    Image {
        id: slipBall
        source: "../../assets/heading_indicator/airplane_shape.png"
        anchors.fill: parent
    }
}
