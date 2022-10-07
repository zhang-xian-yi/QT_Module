import QtQuick 2.0

Rectangle{
    width: 480
    height: 320
    Text {
        id: first
        text: qsTr("hello word")
        font.pointSize: 24

        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.top: parent.top
        anchors.topMargin: 4
    }
    Text {
        id: secend
        color: "black"
        text: qsTr("secend blue  <font color=\"blue\">Text</font>")
        font.pointSize: 24
        font.underline: true
        wrapMode: Text.WordWrap
        //省略 文本右
        //elide: Text.ElideRight
        anchors.left: first.left
        anchors.leftMargin: 4
        anchors.top: first.bottom
        anchors.topMargin: 20
    }

    Text {
        id: third
        text: qsTr("third ")
        font.pointSize: 24
        //文字特效
        style: Text.Outline
        styleColor: red
        anchors.left: secend.left
        anchors.leftMargin: 4
        anchors.top: secend.bottom
        anchors.topMargin: 20
    }




}
