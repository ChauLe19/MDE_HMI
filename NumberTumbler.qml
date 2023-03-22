import QtQuick
import QtQuick.Window
import QtQuick.Controls

Rectangle {
    id: tumbler
    width: frame.implicitWidth
    height: frame.implicitHeight
    color: "#2A2C3A"

    property int value: frame.valueTumblerRow.valueTumbler100.currentIndex * 100 + frame.valueTumblerRow.valueTumbler10.currentIndex * 10 + frame.valueTumblerRow.valueTumbler1.currentIndex

    function setValue(value) {
        var value100 = value/100;
        var value10 = value%100/10;
        var value1 = value%10;
        valueTumbler1.currentIndex = value1
        valueTumbler10.currentIndex = value10
        valueTumbler100.currentIndex = value100
    }


    // keep if needed
    function formatText(count, modelData) {
        var data = count === 12 ? modelData + 1 : modelData;
        return data.toString().length < 2 ? "0" + data : data;
    }

    FontMetrics {
        id: fontMetrics
        font.pointSize: 14
    }

    Component {
        id: delegateComponent

        Label {
            text: modelData
            opacity: 1.0 - Math.abs(Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: fontMetrics.font.pixelSize * 1.25
            color: "white"
        }
    }

    Frame {
        id: frame
        implicitWidth: 240
        implicitHeight: 200
        padding: 0
        anchors.centerIn: parent
        property alias valueTumblerRow: valueTumblerRow

        Row {
            id: valueTumblerRow

            property alias valueTumbler100: valueTumbler100
            property alias valueTumbler10: valueTumbler10
            property alias valueTumbler1: valueTumbler1

            Tumbler {
                id: valueTumbler100
                model: 10
                delegate: delegateComponent
                visibleItemCount: 3
                height: frame.implicitHeight
                width: frame.width/3
                readonly property int value: currentIndex
            }

            Tumbler {
                id: valueTumbler10
                model: 10
                delegate: delegateComponent
                visibleItemCount: 3
                height: frame.implicitHeight
                width: frame.width/3
                readonly property int value: currentIndex
            }

            Tumbler {
                id: valueTumbler1
                model: 10
                delegate: delegateComponent
                visibleItemCount: 3
                height: frame.implicitHeight
                width: frame.width/3
                readonly property int value: currentIndex
            }
        }
    }
}
