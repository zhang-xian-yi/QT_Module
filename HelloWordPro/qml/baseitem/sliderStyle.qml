import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle{
    width: 480;
    height: 320;
    color: "lightgray";

    Slider{
        id:slider_view;
        width: 26;
        height: 200;
        //垂直
        orientation: Qt.Vertical;
        //刻度盘
        tickmarksEnabled: true;
        maximumValue: 100;
        minimumValue: 0;
        value: 1;
        stepSize: 1;

        anchors.right: parent.right;
        anchors.margins: 3;
        style: SliderStyle{
            groove: Rectangle{
                implicitHeight: 20;
                implicitWidth: 200;
                color: "gray";
                radius: 8;
            }

            handle: Rectangle{
                anchors.centerIn: parent;
                color: control.hovered ? "white":"lightgray";
                border.color: control.hovered ? "gray":"blackblue";
                border.width: 2;
                width: 34;
                height: 34;
                radius: 12;
                Text {
                    anchors.centerIn: parent;
                    text: control.value +"%";
                    color: "red";
                }
            }
        }
    }
}
