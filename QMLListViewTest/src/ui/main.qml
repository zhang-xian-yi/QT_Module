import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World");
    signal signal_msg(var psot_msg);

    Item {
        anchors.fill: parent;
        ListView {
            id: listview
            anchors.fill: parent
            model: ServicerModel;
            delegate: Text {
                text: "Data: " + name + ", " + type+","+describe+","+price;
            }
        }
    }

    Connections{
        target: listview.model;
        onDataChanged:{
           ServicerModel.doLog("xxxxxxxx");

        }
        onWriteData:{
            console.log("qml recv c++ data"+data);
        }
    }
}
