import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import "../gauges"


Item {

    width: 1200
    height: 800


    Airspeed {
        id: airspeed
        ias: qSimPanel.flightData.kt_ias ? qSimPanel.flightData.kt_ias : 0
    }


    ArtificialHorizon {
        id: artificialHorizon
        x: 285
        roll: qSimPanel.flightData.roll ? qSimPanel.flightData.roll : 25
        pitch: qSimPanel.flightData.pitch ? qSimPanel.flightData.pitch : 10
    }

    Altimeter {
        id: altimeter
        x: 570
        altitude: qSimPanel.flightData.altitude_ind ? qSimPanel.flightData.altitude_ind : 40
        pressure: qSimPanel.flightData.inhg_baro_pressure ? qSimPanel.flightData.inhg_baro_pressure : 29.91
    }

    CourseDeviationIndicator {
        id: cdi
        x: 870
        course: qSimPanel.flightData.nav1_course ? qSimPanel.flightData.nav1_course: cdi.course
        fromToStatus: qSimPanel.flightData.nav1_from_to_status // todo resolve undefined issue
        glideStatus:  qSimPanel.flightData.nav1_glideslope_status // todo resolve undefined issue
        courseDeviation: qSimPanel.flightData.nav1_course_deviation ? qSimPanel.flightData.nav1_course_deviation : cdi.courseDeviation
        glideslopeDeviation: qSimPanel.flightData.nav1_glideslope_deviation ? qSimPanel.flightData.nav1_glideslope_deviation : cdi.glideslopeDeviation
    }

    TurnCoordinator {
        id: turnCoordinator
        y: 302
        roll: qSimPanel.flightData.roll ? qSimPanel.flightData.roll : 0
        slipDeviation: qSimPanel.flightData.sideslip ? qSimPanel.flightData.sideslip : 0
    }


    HeadingIndicator {
        id: headingIndicator
        x: 285
        y: 302
        heading: qSimPanel.flightData.vacuum_heading ? qSimPanel.flightData.vacuum_heading : 17
    }


    VerticalSpeed {
        id: verticalspeed
        x: 570
        y: 302
        rate: qSimPanel.flightData.vertical_speed ? qSimPanel.flightData.vertical_speed : 0
    }

}
