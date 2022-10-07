﻿import QtQuick 2.2
import QtQuick.Layouts 1.3

Rectangle{
    id:root;
    width: 480;
    height: 320;
    color: "#EEEEEE";

    Text {
        id: txt_show;
        text: qsTr("A single Text");
        anchors.centerIn: parent;
        font.pointSize: 32;
        font.bold: true;
    }

    function setTxtColor(clr)
    {
        txt_show.color = clr;
    }

    GridLayout{
        id:components;
        anchors.left: parent.left;
        anchors.leftMargin: 5;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 5;
        width: 480;
        rows:  3;
        columns: 3;
        rowSpacing: 4;
        columnSpacing: 4;
        flow: Grid.TopToBottom;

        ColorClicker{
            color: Qt.rgba(Math.random(),Math.random(),Math.random(),1.0);
            onHover_signal: setTxtColor(i_color);
        }
        ColorClicker{
            color: Qt.rgba(Math.random(),Math.random(),Math.random(),1.0);
            onHover_signal: setTxtColor(i_color);
        }
        ColorClicker{
            color: Qt.rgba(Math.random(),Math.random(),Math.random(),1.0);
            onHover_signal: setTxtColor(i_color);
        }
        ColorClicker{
            color: Qt.rgba(Math.random(),Math.random(),Math.random(),1.0);
            onHover_signal: setTxtColor(i_color);
        }
        ColorClicker{
            color: Qt.rgba(Math.random(),Math.random(),Math.random(),1.0);
            onHover_signal: setTxtColor(i_color);
        }
        ColorClicker{
            color: Qt.rgba(Math.random(),Math.random(),Math.random(),1.0);
            onHover_signal: setTxtColor(i_color);
        }
        ColorClicker{
            color: Qt.rgba(Math.random(),Math.random(),Math.random(),1.0);
            onHover_signal: setTxtColor(i_color);
        }
        ColorClicker{
            color: Qt.rgba(Math.random(),Math.random(),Math.random(),1.0);
            onHover_signal: setTxtColor(i_color);
        }
        ColorClicker{
            color: Qt.rgba(Math.random(),Math.random(),Math.random(),1.0);
            onHover_signal: setTxtColor(i_color);
        }
        ColorClicker{
            color: Qt.rgba(Math.random(),Math.random(),Math.random(),1.0);
            onHover_signal: setTxtColor(i_color);
        }
    }
}
