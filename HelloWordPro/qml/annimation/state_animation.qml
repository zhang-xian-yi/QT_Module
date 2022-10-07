import QtQuick 2.0

Rectangle{
    id:root_item;
    width: 640;
    height: 480;
    color: "#eeeeee";

    Rectangle{
        id:rect;
        color: "gray";
        width: 50;
        height: 50;
        anchors.centerIn: parent;

        MouseArea{
            id:m_area;
            anchors.fill: parent;
        }

        states: [
            State{
                name:"pressed";
                when: m_area.pressed;
                changes: [
                    PropertyChanges {
                        target: rect;
                        color:"blue";
                        //放大两倍
                        scale:"2.0";

                    }
                ]
            }
        ]

        transitions: Transition {
            id:pressed;
            reversible: true;
            SequentialAnimation{
                NumberAnimation{
                    property: "scale";
                    easing.type: Easing.InOutQuad;
                    duration: 2000;
                }

                ColorAnimation {
                    duration: 600;
                }
            }
        }
    }
}
