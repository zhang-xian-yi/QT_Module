import QtQuick 2.0
import QtQuick.Controls 2.0


Rectangle{
    width: 480;
    height: 320;
    color: "gray";

    focus: true;
    Keys.enabled: true;
    Keys.onEscapePressed: {
        Qt.quit();
    }
    Keys.forwardTo: [moveText,likeQt]

    Text {
        id: moveText;
        text: qsTr("Hello Word!!");
        width: 200;
        height: 30;
        //xy 坐标
        x:20;
        y:20;
        color: "blue";
        font {
            bold: true;
            pointSize: 24;
        }
        Keys.enabled: true;
        Keys.onPressed: {
            switch(event.key)
            {
            case Qt.Key_Left:
                x -=10;
                break;
            case Qt.Key_Right:
                x += 10;
                break;
            case Qt.Key_Up:
                y -= 10;
                break;
            case Qt.Key_Down:
                y += 10;
                break;
            default:return;
            }
            event.accepted = true;
        }
    }
    CheckBox{
        id:likeQt;
        text: "like qt quick";

        anchors.left: parent.left;
        anchors.leftMargin: 5;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 5;
        z:1;
    }
}
