import QtQuick 2.0


Rectangle {
    width: 480;
    height: 320;
    color: "gray";

    Text {
        id: txt;
        text: qsTr("Hello word !!!");
        font.pointSize: 28;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 10;
    }

    Component {
        id:color_component;
        Rectangle {
            id:color_picker;
            width: 50;
            height: 30;
            signal color_clicked_signal(color clr);
            MouseArea {
                anchors.fill: parent;
                onPressed: {
                    color_picker.color_clicked_signal(color_picker.color);
                }
            }
        }
    }
    Loader {
        id:red_loader;
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        anchors.margins: 5;

        sourceComponent: color_component;
        onLoaded: {
            item.color = "red";
        }
    }
    Connections {
        target: red_loader.item;
        onColor_clicked_signal:{
            txt.color = clr;XQ
        }
    }

    Loader {
        id:blue_loader;
        anchors.left: red_loader.right;
        anchors.leftMargin: 5;
        anchors.top: red_loader.top;

        sourceComponent: color_component;
        onLoaded: {
            item.color = "blue";
        }
    }



    Connections {
        target: red_loader.item;
        onColor_clicked_signal:{
            txt.color = clr;XQ
        }
    }

    Connections {
        target: blue_loader.item;
        onColor_clicked_signal:{
            txt.color = clr;
        }
    }






}
