import QtQuick 2.0

Rectangle{
    id:root;
    width: 640;
    height: 480;
    color: "#eeeeee";
    property bool is_hovered: false;
    Rectangle{
        id:rect;
        width: 50;
        height: 150;
        anchors.centerIn: parent;
        color: "blue";

        PropertyAnimation on width{
            id:rect_anima;
            to:250;
            //动画持续时间1000 毫秒
            duration: 1000;
            running: is_hovered;
        }

        MouseArea{
            id:marea;
            hoverEnabled: true;
            anchors.fill: parent;
            onClicked: {
                rect.width = 50;
            }
            onEntered: {
                is_hovered = true;
            }
            onExited: {
                is_hovered = false;
            }
        }
    }

}
