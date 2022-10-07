import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle{
    width: 480
    height: 320

    Button{
        height: 30
        id:btn_open
        text: "打开"
        anchors.left: parent.left
        anchors.leftMargin: 1
        anchors.top: parent.top
        anchors.topMargin: 1
    }

    Button{
        height: 30
        id:btn_quit
        text: "退出"
        anchors.left: btn_open.right
        anchors.leftMargin: 4
        anchors.bottom: btn_open
    }
}
