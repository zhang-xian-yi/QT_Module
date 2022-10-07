import QtQuick 2.12

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

    MouseArea{
        id:m_area;
        anchors.fill: parent;
        //开启悬停事件处理
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
    Keys.onEnterPressed: {
        hover_signal(color_clicker.color);
        event.accept = true;
    }

    Keys.onEscapePressed: {
        hover_signal(color_clicker.color);
        event.accept = true;
    }

    onFocusChanged: {
        configureBorder();
    }

    Component.onCompleted: {
        configureBorder();
    }
}
