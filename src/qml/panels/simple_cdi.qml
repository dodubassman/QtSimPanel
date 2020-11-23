import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import "../gauges"


Item {

    width: 800
    height: 800

    CourseDeviationIndicator {
        id: cdi
        course: qSimPanel.flightData.nav1_course ? qSimPanel.flightData.nav1_course: cdi.course
        fromToStatus: qSimPanel.flightData.nav1_from_to_status // todo resolve undefined issue
        glideStatus:  qSimPanel.flightData.nav1_glideslope_status // todo resolve undefined issue
        courseDeviation: qSimPanel.flightData.nav1_course_deviation ? qSimPanel.flightData.nav1_course_deviation : cdi.courseDeviation
        glideslopeDeviation: qSimPanel.flightData.nav1_glideslope_deviation ? qSimPanel.flightData.nav1_glideslope_deviation : cdi.glideslopeDeviation
    }
}
