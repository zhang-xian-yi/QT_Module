import QtQuick 2.2

Rectangle{
    width: 480;
    height: 320;
    color: "#EEEEEE";

    Component{
        id:picked_component;
        Rectangle{
            id:color_clicker;
            width: 30;
            height: 30;
            signal hover_signal(color i_color);

            function configureBorder()
            {
                color_clicker.border.width = color_clicker.focus ? 10:5;
                color_clicker.border.color = color_clicker.focus ? "#90d750" : "#808080";
            }
            border.width: focus ? 2: 0;
            border.color: focus ? "#90d7f0":"#808080";
            MouseArea{
                id:m_area;
                anchors.fill: parent;
                //开启悬停事件处理
                enabled: true;
                hoverEnabled: true;
                onEntered: {
                    //如果鼠标悬停在区域内
                    hover_signal(color_clicker.color);
                    mouse.accept = true;
                    color_clicker.focus = true;
                }
                onExited: {
                    //鼠标悬停在区域外
                    hover_signal(color.black);
                    mouse.accept = true;
                    color_clicker.focus = true;
                }
            }

            Keys.enabled: true;
            Keys.onEscapePressed: {
                configureBorder();
                event.accept = true;

            }
            Keys.onEnterPressed: {
                configureBorder();
                event.accept = true;
            }
        }
    }

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
        sourceComponent: picked_component;

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
        sourceComponent: picked_component;

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
        }
    }

    Connections{
        target: blue_loader.item;
        onHover_signal:{
            setTextColor(i_color);
        }
    }

}
