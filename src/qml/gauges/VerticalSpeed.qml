import QtQuick 2.6
import QtQuick.Window 2.2

Item {
    id: altimeter
    visible: true
    width: 256
    height: 256

    property int rate: 0

    onRateChanged: {
        // Linera interpolation
        var x = rate/100;
        var x0, y0;
        var x1, y1;


        // Limit max values
        if (x >= 20) {
            x = 20;
        }
        if (x <= -20) {
            x = -20;
        }

        var knownValues = [
                    [-20, -175],
                    [-15, -127],
                    [-10, -80],
                    [-5, -35],
                    [0, 0],
                    [5, 35],
                    [10, 80],
                    [15, 127],
                    [20, 175]
                ];

        for (var i = 0 ; i <= knownValues.length ; i++) {
            if(x >= knownValues[i][0] && x <= knownValues[i+1][0]) {
               x0 = knownValues[i][0];
               y0 = knownValues[i][1];
               x1 = knownValues[i+1][0];
               y1 = knownValues[i+1][1];
               break;
            }
        }

        needleLayer.rotation  = x >= 20
                ? 175 // Max value 175
                : y0 + (x-x0)*((y1-y0)/(x1-x0)); // See en.wikipedia.org/wiki/Linear_interpolation
    }


    Image {
        id: backgroundLayer
        source: "../../assets/vertical_speed/background.svg"
        anchors.fill: parent
    }

    Image {
        id: needleLayer
        source: "../../assets/vertical_speed/needle.svg"
        anchors.fill: parent
        Behavior on rotation {
            RotationAnimation { duration: 500; direction: RotationAnimation.Shortest }
        }

    }
}
