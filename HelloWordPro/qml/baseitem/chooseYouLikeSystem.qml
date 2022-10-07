import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4


Rectangle{
    id:root;
    width: 480;
    height: 320;
    color: "#a0a0a0";

    //结果显示
    Rectangle{
        id:result_holder;
        width: 200;
        height: 60;
        //透明度
        opacity: 0.7;
        anchors.centerIn: parent;
        color: "gray";
        border.color: "#a0a0a0";
        border.width: 2;
        //不可见
        visible: false;
        Text {
            id: result_txt;
            anchors.centerIn: parent;
            font.pointSize: 20;
            color: "blue";
            font.bold: true;
        }
    }

    Component{
        id:radio_style;
        RadioButtonStyle{
            //绘制背景图案
            background: Rectangle{
                implicitWidth: control.width;
                implicitHeight: control.height;
                opacity: 0.3;
                color: control.color;
            }

            indicator: Rectangle{
                implicitWidth: 16;
                implicitHeight: 12;
                radius: 6;
                border.color: control.hovered ? "darkblue":"gray";
                border.width:2;
                Rectangle{
                   anchors.fill: parent;
                   visible: control.checked;
                   color: "#0000a0";
                   radius: 5;
                   anchors.margins: 3;
                }
            }
            label: Text {
                color:control.activeFocus ? "blue":"black";
                anchors.centerIn: parent;
                text: control.text;
            }
        }
    }

    Text {
        id: remind;
        text: qsTr("please selected the best moblie phone system");
        anchors.top: parent.top;
        anchors.topMargin: 16;
        anchors.left: parent.left;
        anchors.leftMargin: 8;
    }

    //定义一个互斥组对象
    ExclusiveGroup{
        id:choose_group;
    }
    RadioButton{
        id:android;
        text:"Android";
        exclusiveGroup: choose_group;
        anchors.top:remind.bottom;
        anchors.topMargin: 8;
        anchors.left: remind.left;
        anchors.leftMargin: 20;
        style: radio_style;
        checked: true;
        focus: true;
        activeFocusOnPress: true;
        onClicked: {
            result_holder.visible = false;
        }
    }
    RadioButton{
        id:ios;
        text:"IOS";
        exclusiveGroup: choose_group;
        anchors.top:android.bottom;
        anchors.topMargin: 8;
        anchors.left: android.left;
        style: radio_style;
        activeFocusOnPress: true;
        onClicked: {
            result_holder.visible = false;
        }
    }
    RadioButton{
        id:wp;
        text:"Windows Phone";
        exclusiveGroup: choose_group;
        anchors.top:ios.bottom;
        anchors.topMargin: 8;
        anchors.left: android.left;
        style: radio_style;
        activeFocusOnPress: true;
        onClicked: {
            result_holder.visible = false;
        }
    }
    RadioButton{
        id:firefox;
        text:"Firefox OS";
        exclusiveGroup: choose_group;
        anchors.top:wp.bottom;
        anchors.topMargin: 8;
        anchors.left: android.left;
        style: radio_style;
        activeFocusOnPress: true;
        onClicked: {
            result_holder.visible = false;
        }
    }
    RadioButton{
        id:sailfish;
        text:"Sailfish OS";
        exclusiveGroup: choose_group;
        anchors.top:firefox.bottom;
        anchors.topMargin: 8;
        anchors.left: android.left;
        style: radio_style;
        activeFocusOnPress: true;
        onClicked: {
            result_holder.visible = false;
        }
    }

    Button{
        id:confirm;
        text: "Confirm";
        anchors.top: sailfish.bottom;
        anchors.topMargin: 8;
        anchors.left: android.left;
        onClicked: {
            result_txt.text = choose_group.current.text;
            result_holder.visible = true;
        }
    }


}


