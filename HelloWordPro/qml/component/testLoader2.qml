import QtQuick 2.2

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

    Loader{
        id:red_loader;
        width: 90;
        height: 90;
        source:  "ColorClicker.qml";

        anchors.left: parent.left;
        anchors.leftMargin: 5;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 5;
        onLoaded: {
            item.color = "red";
        }
        onFocusChanged: {
            item.focus = focus;
        }
    }

    //不限制loader 的大小
    Loader{
        id:blue_loader;
        source:  "ColorClicker.qml";

        anchors.left: red_loader.right;
        anchors.leftMargin: 5;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 5;
        onLoaded: {
            blue_loader.item.color = "blue";
        }
        onFocusChanged: {
            blue_loader.item.focus = focus;
        }
    }

    Connections{
        target: red_loader.item;
        onHover_signal:{
            setTextColor(i_color);
            //设置loader 的焦点
            if(!red_loader.focus)
            {
                red_loader.focus = true;
                blue_loader.focus=false;
            }
        }
    }

    Connections{
        target: blue_loader.item;
        onHover_signal:{
            setTextColor(i_color);
            if(!blue_loader.focus)
            {
                blue_loader.focus=true;
                red_loader.focus = false;
            }
        }
    }

}
