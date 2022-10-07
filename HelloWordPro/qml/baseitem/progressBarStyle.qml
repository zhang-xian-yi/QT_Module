import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle{
    width:480;
    height: 320;
    color: "#a0b0c0";

    Row{
        anchors.fill: parent;
        anchors.margins: 8;
        spacing: 4;

        ProgressBar{
            id:custom;
            width: 150;
            height: 20;
            minimumValue: 0;
            maximumValue: 100;
            value: 10;
            style: ProgressBarStyle{
                id:progress_style;
                background: Rectangle{
                    border.color: (control.hovered) ? "green":"gray";
                    border.width: 1;
                    color: "lightgray";
                }
                progress: Rectangle{
                    color:"#208020";
                }
                panel: Item{
                    implicitHeight: 20;
                    implicitWidth: 200;
                    Loader{
                        anchors.fill: parent;
                        sourceComponent: background;
                    }
                    Loader{
                        id:pro_loader;
                        anchors.top: parent.top;
                        anchors.left: parent.left;
                        anchors.bottom: parent.bottom;
                        anchors.margins: 3;
                        z:1;
                        width: currentProgress * (parent.width - 6);
                        sourceComponent: progress_style.progress;
                    }
                    Text {
                        color: "blue";
                        text: currentProgress * 100 + "%";
                        z:2;
                        anchors.centerIn: parent;
                    }
                }
            }

            Timer{
                interval: 1000;
                repeat: true;
                running: true;
                triggeredOnStart: true;
                onTriggered: {
                    if(parent.value <99.1)
                    {
                        parent.value += 1;
                    }
                    else
                    {
                        stop();
                    }
                }
            }
        }

    }
}
