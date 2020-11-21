import QtQuick 2.6
import QtQuick.Window 2.2

Item {
    id: courseDeviationIndicator
    visible: true
    width: 256
    height: 256

    property real course: 365.0
    property int fromToStatus: 0
    property int glideStatus: 1
    property real courseDeviation: 0
    property real glideslopeDeviation: 0

    Image {
        id: gradution
        source: "../../assets/course_deviation_indicator/graduations.png"
        anchors.fill: parent
    }


    Image {
        id: gs_marker
        visible: (glideStatus == 1)
        source: "../../assets/course_deviation_indicator/gs_marker.png"
        anchors.fill: parent
    }

    Image {
        id: gs_mask
        source: "../../assets/course_deviation_indicator/gs_mask.png"
        anchors.fill: parent
    }

    Image {
        id: nav_marker
        visible: (fromToStatus == 0)
        source: "../../assets/course_deviation_indicator/nav.png"
        anchors.fill: parent
    }

    Image {
        id: nav_mask
        source: "../../assets/course_deviation_indicator/nav_mask.png"
        anchors.fill: parent
    }


    Image {
        id: to
        visible: (fromToStatus == 1)
        source: "../../assets/course_deviation_indicator/to.png"
        anchors.fill: parent
    }

    Image {
        id: from
        visible: (fromToStatus == 2)
        source: "../../assets/course_deviation_indicator/from.png"
        anchors.fill: parent
    }

    Image {
        id: gs
        source: "../../assets/course_deviation_indicator/glide.png"
        y: glideslopeDeviation/2.5*80
        Behavior on y {
            NumberAnimation { duration: 300 }
        }        width: 256
        height: 256
    }

    Image {
        id: loc
        source: "../../assets/course_deviation_indicator/localizer.png"
        x: courseDeviation/2.5*80
        Behavior on x {
            NumberAnimation { duration: 300 }
        }
        width: 256
        height: 256
    }

    Image {
        id: mask
        source: "../../assets/course_deviation_indicator/masks.png"
        anchors.fill: parent
    }

    Image {
        id: cog
        source: "../../assets/course_deviation_indicator/cap.png"
        anchors.fill: parent
        rotation: -course
        Behavior on rotation {
            RotationAnimation { duration: 100; direction: RotationAnimation.Shortest }
        }

    }

}
