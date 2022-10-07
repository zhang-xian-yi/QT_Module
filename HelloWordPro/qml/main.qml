import QtQuick.Window 2.2
import QtQuick 2.2
import QtQuick.Controls 2.0


Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("hw")
    Rectangle{
        x:10;
        y:10;
        height: 100;
        width: 100;
        color: "red";
        opacity: 0.1;
    }

    Text {
        id: text_id
        text: qsTr("Hello word")
        anchors.centerIn: parent
    }


}
