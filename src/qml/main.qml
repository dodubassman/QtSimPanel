import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import "gauges"


Window {

    visibility: Window.FullScreen
    color: "#000000"
    visible: true
    width: 800
    height: 480
    title: qsTr("QtSimPanel")

    Item {
        id: instructions
        width: 300
        height: 300
        visible: qSimPanel.areInstructionsVisible
        anchors.right: parent.right
        Text {
            id: title
            text: qsTr("OpenSimPanel")
            font.family: "Sans";
            font.pointSize: 25;
            color: "white";
            anchors.horizontalCenter: parent.horizontal
            bottomPadding: 0
        }

        Text {
            anchors.top: title.bottom
            text: "
<strong>Key binding:</strong>
<pre>
I       Show/hide this information message
S       Save configuration
↑/↓/←/→ Adjust panel position
+/-     Adjust panel scale
Esc     Quit OpenSimPanel
</pre>"
            font.family: "Monospace";
            color: "white";

        }
    }

    Panel {
        id: panel
        transform: Scale {
            yScale: qSimPanel.panelScale
            xScale: qSimPanel.panelScale
        }
        x: qSimPanel.panelPositionX
        y: qSimPanel.panelPositionY
    }

}
