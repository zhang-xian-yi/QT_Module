import QtQuick 2.0
import QtQuick.Controls 1.2

Rectangle{
    width: 480;
    height: 320;
    color: "gray";

    QtObject{
        id:attrs;
        property int count_num;
        Component.onCompleted: {
            attrs.count_num = 10;
        }
    }
    Text {
        id: txt_calp;
        text: qsTr("10")
        font.pointSize:40;
        anchors.horizontalCenter: parent.horizontalCenter;
    }
    Timer{
        id:timer_count_down;
        repeat: true;
        //毫秒单位
        interval: 1000;
        //定时器启动之时立刻执行一次
        triggeredOnStart: true;
        onTriggered: {
            txt_calp.text = attrs.count_num;
            attrs.count_num -= 1;
            if(attrs.count_num <= 0)
            {
                timer_count_down.stop();
                txt_calp.text = "finish timer task";
            }
        }
    }
    Button {
        id:btn_start;
        text: "Start";
        anchors.horizontalCenter : parent.horizontalCenter;
        anchors.top: txt_calp.bottom;
        anchors.topMargin: 20;

        onClicked: {
            attrs.count_num = 10;
            timer_count_down.start();
        }
    }
}
