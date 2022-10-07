import QtQuick 2.0

Rectangle{
    width: 640;
    height: 480;
    id:root_item;
    color: "#eeeeee";


    Rectangle{
        id:rect;
        width: 100;
        height: 100;
        color: "#c0c0c0";
        MouseArea{
            id:marea;
            anchors.fill: parent;
            onClicked: {

            }
        }


        ColorAnimation{
            from: "#c0c0c0";
            to: "black"
            loops: Animation.Infinite;
            duration: 3000;
        }
    }


}
