import QtQuick 2.0

Rectangle{
    id:root_item;
    width:3200;
    height: 240;

    Rectangle{
        id:rect;
        width: 160;
        height: 100;
        color: "red";
        anchors.centerIn: parent;

        Behavior on width {
            NumberAnimation { duration: 1000}
        }

        Behavior on height {
            NumberAnimation { duration: 1000; easing.type: Easing.InCubic}
        }

        MouseArea{
            id:m_area;
            anchors.fill: parent;
            onClicked: {
                rect.width = Math.random() * root_item.width;
                rect.height = Math.min(Math.random() * root_item.height,rect.height*1.5);
            }
        }
    }
}
