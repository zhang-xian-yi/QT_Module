import QtQuick 2.0
import QtQuick.Controls 1.4

import cn.HelloWord.fun 1.0


Rectangle{
    width: 480;
    height: 320;
    Text {
        id: time_label;
        anchors.top: parent.top;
        anchors.topMargin: 4;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        font.pointSize: 24;
    }

    ColorMaker{
        id:color_maker;
        color: Qt.green;
    }

    Rectangle{
        id:color_rect;
        anchors.centerIn: parent;
        width: 200;
        height: 200;
        color: "blue";
    }

    Button{
        id:start;
        text: "Start";
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        onClicked: {
            color_maker.start();
        }
    }
    Button{
        id:stop;
        text: "Stop";
        anchors.left: start.right;
        anchors.leftMargin: 4;
        anchors.bottom: start.bottom;
        onClicked: {
            color_maker.start();
        }
    }

    /*

    enum GenerateAlgorithm{
        RandomRGB,
        RandomRed,
        RandomGreen,
        RandomBlue,
        LinearIncrease
    };
      */
    function changeAlgorithmBtn(button,algorithm)
    {
        switch(algorithm)
        {
            case 0:
            {
                button.text = "RandomRGB";
                break;
            }
            case 1:
            {
                button.text = "RandomRed";
                break;
            }
            case 2:
            {
                button.text = "RandomGreen";
                break;
            }
            case 3:
            {
                button.text = "RandomBlue";
                break;
            }
            case 4:
            {
                button.text = "LinearIncrease";
                break;
            }
        }
    }

    Button{
        id:algorithm;
        text: "GeneralColor";
        anchors.left: stop.right;
        anchors.leftMargin: 4;
        anchors.bottom: start.bottom;
        onClicked: {
            var algorithm_get = (color_maker.getAlgorithm() + 1)%5;
            changeAlgorithmBtn(algorithm,algorithm_get);
            color_maker.setAlgorithm(algorithm_get);
        }
    }

    Button{
        id:quit;
        text:"Quit";
        anchors.left: algorithm.right;
        anchors.leftMargin: 4;
        anchors.bottom: start.bottom;
        onClicked: {
            Qt.quit();
        }
    }

    Component.onCompleted: {
        color_maker.color = Qt.rgba(0,180,220,225);
        color_maker.setAlgorithm(color_maker.LinearIncrease);
        changeAlgorithmBtn(algorithm,color_maker.LinearIncrease);
    }

    Connections{
        target: color_maker;
        onCurrentTime:{
             time_label.text = "strTime";
             time_label.color = color_maker.time_color;
        }
    }

    Connections{
        target: color_maker;
        onColorChanged:{
            color_rect.color = color;
        }
    }
}
