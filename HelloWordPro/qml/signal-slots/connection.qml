import QtQuick 2.2
import QtQuick.Controls 2.2

Rectangle{
    width: 480;
    height: 320;

    color: "gray";

    Text {
        id: txt1
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        text: qsTr("text one")
        font.pointSize: 28
        color: "blue"
    }

    Text {
        id: txt2
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: txt1.bottom
        anchors.topMargin: 10
        text: qsTr("text two")
        font.pointSize: 28
        color: "red"
    }

    Button {
        id:btn_change
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: txt2.bottom
        anchors.topMargin: 10

        text:"改变颜色"
    }

    Connections {
        target: btn_change;
        onClicked:{
            txt1.color = Qt.rgba(Math.random(),Math.random(),Math.random(),1);
            txt2.color = Qt.rgba(Math.random(),Math.random(),Math.random(),1);
        }
    }


}
