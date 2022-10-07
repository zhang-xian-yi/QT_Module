import QtQuick 2.0

Rectangle{
    width: 360;
    height: 240;
    color: "#eeeeee";
    id:root_item;

    Rectangle{
        id:blue_rect;
        width: 100;
        height: 100;
        color: "blue";
        anchors.top: parent.top;
        anchors.topMargin: 8;
        anchors.left: parent.left;
        anchors.leftMargin: 8;
    }


    Rectangle{
        id:red_rect;
        width: 100;
        height: 100;
        color: "red";
        anchors.leftMargin: 10;
        state: "default";

        MouseArea{
            id:m_area;
            anchors.fill: parent;
            onClicked: {
                if(red_rect.state == "" || red_rect.state == "default")
                {
                    red_rect.state = "reanchor";
                }
                else
                {
                    red_rect.state = "default";
                }
            }
        }
        states:[
            State {
                name: "reanchor";
                changes:[
                    AnchorChanges{
                  target: red_rect;
                 anchors.top: blue_rect.bottom;
                 anchors.left: root_item.left;
                    },
                    PropertyChanges {
                        target: red_rect;
                        height:40;
                        anchors.topMargin: 4;
                    }
                ]
            },
            State {
                name: "default"
                changes:AnchorChanges{
                    target: red_rect;
                    anchors.left: blue_rect.right;
                    anchors.top: blue_rect.top;
                }
            }

        ]

        transitions: Transition {
            AnchorAnimation{
             duration: 1000;
             //easing.type: Easing.OutInCubic;
            }
        }
    }

}
