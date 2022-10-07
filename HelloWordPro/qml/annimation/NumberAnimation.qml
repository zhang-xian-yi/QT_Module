import QtQuick 2.6

Rectangle{
    width: 640;
    height:480;
    color: "#eeeeee";
    id:root_item;

    Rectangle{
        id:rect;
        color: "blue";
        width: 50;
        height: 50;
        x:0;
        y:95;

        MouseArea{
            id:m_area;
            anchors.fill: parent;
            onClicked: {
                if(anima.paused)
                {
                    anima.resume();
                }
                else if(anima.running)
                {
                    anima.pause();
                }
                else
                {
                    rect.x = 0;
                    rect.radius = 0;
                    rect.rotation = 0
                    anima.start();
                }
            }
        }


        ParallelAnimation{
            id:anima;
            running: false;
            NumberAnimation{
                id:animation_x;
                target: rect;
                property: "x";
                to:640;
                loops: Animation.Infinite;
                duration: 3000;
                running: false;
                easing.type: Easing.OutCubic;
            }
            NumberAnimation{
                target: rect;
                property: "rotation";
                id:animation_r;
                to:2160;
                loops: Animation.Infinite;
                duration: 3000;
                running: false;
                easing.type: Easing.OutInCirc;
            }

            NumberAnimation {
                id:animation_radius;
                to:20;
                target: rect;
                property: "radius";
                duration: 3000;
                running: false;
                easing.type: Easing.OutInCirc;
            }
        }


    }

}
