import QtQuick 2.0

Rectangle{
    width: 480;
    height: 320;
    color: "#EEEEEE";


    Text {
        id: txt_show;
        text: qsTr("Hello Word!!!");
        font.pointSize: 32;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 5;
    }

    function setTextColor(clr)
    {
        txt_show.color = clr;
    }

    ColorClicker{
        id:redColor;
        color: "red";
        anchors.left: parent.left;
        anchors.leftMargin: 5;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 5;

        onHover_signal: {
            setTextColor(i_color);
        }
    }

    ColorClicker{
        id:blueColor;
        color: "blue";
        anchors.left: redColor.right;
        anchors.leftMargin: 5;
        anchors.bottom: redColor.bottom;

        onHover_signal: {
            setTextColor(i_color);
        }
    }

    ColorClicker{
        id:yellowColor;
        color: "yellow";
        anchors.left: blueColor.right;
        anchors.leftMargin: 5;
        anchors.bottom: blueColor.bottom;

        onHover_signal: {
            setTextColor(i_color);
        }
    }

}
