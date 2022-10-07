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
        color: "red";
        state: "default";

        MouseArea{
            id:m_area;
            anchors.fill: parent;
            onClicked: {
                if(red_rect.state == "" || red_rect.state == "default")
                {
                    red_rect.state = "reparent";
                }
                else
                {
                    red_rect.state = "default";
                }
            }
        }
        states:[
            State {
                name: "reparent";
                changes:[ParentChange{
                  target: red_rect;
                  parent: blue_rect;
                  width: 50;
                  height:50;
                  x:blue_rect.x + 25 - 8;
                  y:blue_rect.x + 25 - 8;
                  //rotation: 4;

                }]
            },
            State {
                name: "default"
                changes:ParentChange{
                    target: red_rect;
                    parent: root_item;
                    width: 100;
                    height: 100;
                    x:blue_rect.x + blue_rect.width + 8;
                    y:blue_rect.y;

                }
            }

        ]

        transitions: Transition {
            ParentAnimation{
             NumberAnimation{properties: "x,y"; duration: 1000;}
            }
        }
    }

}
