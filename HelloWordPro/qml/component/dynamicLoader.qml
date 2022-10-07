import QtQuick 2.0
import QtQuick.Controls 2.4

Rectangle{
    id:root_item;
    width: 480;
    height: 320;
    color: "#eeeeee";
    property bool is_show_component: false;

    Text {
        id: txt_show;
        text: qsTr("Hello Word !!!");
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 5;
        font.pointSize: 32;
    }
    Button{
        id:btn_show;
        text: "SHOW";
        anchors.left: parent.left;
        anchors.leftMargin: 5;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 5;

        onClicked: {
            //如果是显示
            if(root_item.is_show_component)
            {
                btn_show.text = "SHOW";
                root_item.is_show_component = false;
                //销毁两对象
                red_loader.source = "";
                blue_loader.source = "";
            }
            else
            {
                btn_show.text = "HIDE";
                root_item.is_show_component = true;
                //创建两对象
                red_loader.source = "ColorClicker.qml";
                red_loader.item.hover_signal.connect(onHover_red);
                blue_loader.source = "ColorClicker.qml";
                blue_loader.item.hover_signal.connect(onHover_blue);
            }
        }
    }

    Loader{
        id:red_loader;
        //占位用 需要动态进行加载
        //source: "ColorClicker.qml";
        anchors.left: btn_show.right;
        anchors.leftMargin: 5;
        anchors.bottom: btn_show.bottom;

        onLoaded: {
            if(item != null)
            {
                item.color = "red";
            }
        }

        onFocusChanged: {
            if(item != null)
            {
                item.focus = focus;
            }
        }
    }
    Loader{
        id:blue_loader;
        //占位用 需要动态进行加载
        //source: "ColorClicker.qml";
        anchors.left: red_loader.right;
        anchors.leftMargin: 5;
        anchors.bottom: red_loader.bottom;

        onLoaded: {
            if(item != null)
            {
                item.color = "blue";
            }
        }

        onFocusChanged: {
            if(item != null)
            {
                item.focus = focus;
            }
        }
    }

    function onHover_red(i_color)
    {
        txt_show.color = i_color;
        if(! red_loader.focus)
        {
            red_loader.focus = true;
            blue_loader.focus = false;
        }
    }

    function onHover_blue(i_color)
    {
        txt_show.color = i_color;
        if(! blue_loader.focus)
        {
            blue_loader.focus = true;
            red_loader.focus = false;
        }
    }

}
