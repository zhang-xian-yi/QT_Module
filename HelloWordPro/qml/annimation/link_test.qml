import QtQuick 2.0

Rectangle{
    id:root_item;
    width: 640;
    height: 480;
    color: "#eeeeee";

    Text {
        id: txt_show;
        text: qsTr("I am a Web Link Txt");
        anchors.centerIn: parent;
        font.pointSize: 24;
        state: "initial";
        property bool is_clicked: false;

        MouseArea{
            id:m_area;
            anchors.fill: parent;
            hoverEnabled: true;
            onEntered: {
                txt_show.state = txt_show.is_clicked == true ? "clicked_hovered":"hovered";
            }
            onExited: {
                txt_show.state = txt_show.is_clicked == true ? "clicked":"initial";
                txt_show.is_clicked = false;
            }

            onClicked: {
                if(txt_show.is_clicked == false)
                {
                    txt_show.is_clicked = true;
                }
                txt_show.state = "clicked";
            }
        }

        states: [
            State {
                name: "initial"
                changes:PropertyChanges {
                    target: txt_show;
                    color:"blue";
                }
            },
            State {
                name: "hovered"
                changes:PropertyChanges {
                    target: txt_show;
                    color:"#87cefa";
                    font{
                        italic: true;
                        pointSize: 36;
                        underline: true;
                    }

                }
            },
            State {
                name: "clicked"
                changes:PropertyChanges {
                    target: txt_show;
                    color:"#8b4513";
                    font{
                        pointSize: 24;
                    }

                }
            },
            State {
                name: "clicked_hover"
                changes:PropertyChanges {
                    target: txt_show;
                    color:"#d2691e";
                    font{
                        italic: true;
                        pointSize: 36;
                        underline: true;
                    }
                }
            }
        ]

        transitions: [
            Transition {
                from: "initial"
                to: "hovered"
                reversible: true;
                NumberAnimation{
                    property: "font.pointSize";
                    duration: 800;
                }
                ColorAnimation {
                    duration: 800
                }

            },
            Transition {
                from: "hovered"
                to: "clicked"
                NumberAnimation{
                    property: "font.pointSize";
                    duration: 800;
                }
                ColorAnimation {
                    duration: 800
                }
            },
            Transition {
                from: "clicked"
                to: "clicked_hover"
                NumberAnimation{
                    property: "font.pointSize";
                    duration: 800;
                }
                ColorAnimation {
                    duration: 800
                }
            }

        ]

    }




}
