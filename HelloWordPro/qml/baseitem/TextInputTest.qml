import QtQuick 2.0


Rectangle{
    id:root;
    width: 480;
    height: 320;

    TextInput{
        id:txt_in;
        //width: 240;
        font.pointSize: 24;
        z:1;
        anchors.horizontalCenter: parent.horizontalCenter;
        focus: true;

        inputMask: "0000-00-00;-";
    }
    Rectangle{
        id:txt_back;
        width: txt_in.width;
        height: txt_in.height;
        color: "blue";

        x:txt_in.x;
        y:txt_in.y;
        z:0.1;
    }
}


