import QtQuick 2.6
import QtQuick.Window 2.2

Item {
    id: airspeed
    visible: true
    width: 256
    height: 256

    property int tas: 0

    onTasChanged: {
        // Linera interpolation
        var x = tas;
        var x0, y0;
        var x1, y1;


        // Limit max values
        if (x >= 200) {
            x = 200;
        }

        var knownValues = [
                    [0, 0],
                    [40, 28],
                    [50, 51],
                    [60, 73],
                    [80, 117],
                    [100, 161],
                    [120, 205],
                    [160, 269],
                    [200, 317]
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

        needleLayer.rotation  = x >= 200
                ? 317 // Max value 317
                : y0 + (x-x0)*((y1-y0)/(x1-x0)); // See en.wikipedia.org/wiki/Linear_interpolation
    }


    Image {
        id: backgroundLayer
        source: "../../assets/airspeed_indicator/background.svg"
        anchors.fill: parent
    }

    Image {
        id: needleLayer
        source: "../../assets/airspeed_indicator/needle.svg"
        anchors.fill: parent
        Behavior on rotation {
            RotationAnimation { duration: 500; direction: RotationAnimation.Shortest }
        }

    }
}
