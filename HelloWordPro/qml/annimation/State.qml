import QtQuick 2.0


Rectangle{
    width: 360;
    height: 240;
    color: "#eeeeee";
    id:root_item;

    Text {
        id: txt_show;
        text: qsTr("a Single Text");
        state: "red_txt";
        anchors.centerIn: parent;
        font.pointSize: 24;

        MouseArea{
            id:m_area;
            anchors.fill: parent;
            onReleased: {
                txt_show.state = "red_txt";
            }
        }

        states:[
            State{
                name: "red_txt";
                changes: [
                    PropertyChanges{target:txt_show;color:"red"}
                ]
            },
            State{
                name: "blue_txt";
                when: m_area.pressed;
                changes: [
                    PropertyChanges{target:txt_show;color:"blue";font.bold: true;font.pointSize: 32;}
                ]
            }
        ]
    }
}
