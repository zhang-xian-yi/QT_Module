import QtQuick 2.9
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import cn.callQML.viewer 1.0


Rectangle{
    width: 640;
    height: 490;
    color: "#121212";

    BusyIndicator{
        id:busy;
        running: false;
        anchors.centerIn: parent;
        z:2;
    }

    Label{
        id:state_label;
        visible: false;
        anchors.centerIn: parent;
    }

    Image {
        objectName: "image_viewer";
        id: image_viewer;
        anchors.fill: parent;
        asynchronous: true;
        fillMode: Image.PreserveAspectFit;
        onStateChanged: {
            if(image_viewer.status === Image.Loading)
            {
                busy.running = true;
                state_label.visible = false;
            }
            else if(image_viewer.status === Image.Ready)
            {
                busy.running = false;
            }
            else if(image_viewer.status === Image.Error)
            {
                busy.running = false;
                state_label.visible = true;
                state_label.text = "Error";
            }
        }
    }

    ImageProcessor{
        id:processor;
        onFinished: {
            console.log("image deal finish");
            image_viewer.source = "file:///"+new_file_;
        }
    }

    FileDialog{
        id:file_dialog;
        title:"Please Choose File";
        nameFilters: ["Image Files (*.jpeg *.jpg *.png *.bmp *.gif)"];
        onAccepted: {
            console.log(file_dialog.fileUrl);
            image_viewer.source = file_dialog.fileUrl;
        }
    }

    Component{
            id:btn_style;
            ButtonStyle{
                background: Rectangle{
                    implicitWidth: 70;
                    implicitHeight: 30;
                    border.color: control.hovered ? "#c0c0c0":"#909090";
                    border.width: control.hovered ? 2:1;
                    color: control.pressed ? "#a0a0a0" : "#7070700";

                    gradient: Gradient{
                        GradientStop{position: 0;color: control.pressed ? "#cccccc" : "#e0e0e0";}
                        GradientStop{position: 1;color: control.pressed ? "#aaa" : "#ccc";}
                    }

                }
                label: Text {
                    anchors.fill: parent;
                    font.pointSize: 21;
                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                    text: control.text;
                    color: (control.hovered && ! control.pressed) ? "blue":"white";
                }
            }
    }

    Button{
        id:open_file;
        text: "Open";
        anchors.top: parent.top;
        anchors.topMargin: 6;
        anchors.left: parent.left;
        anchors.leftMargin: 6;
        style: btn_style;
        z:1;
        onClicked: {
            file_dialog.visible = true;
        }

    }

    Button{
        id:quit;
        text: "Quit";
        anchors.left: open_file.right;
        anchors.leftMargin: 4;
        anchors.bottom: open_file.bottom;
        style: btn_style;
        z:1;
        onClicked: {
            Qt.quit();
        }
    }

    Rectangle{
        anchors.left: parent.left;
        anchors.top: parent.top;
        anchors.bottom: open_file.bottom;
        anchors.bottomMargin: -6;
        anchors.right: quit.right;
        anchors.rightMargin: -6;
        color: "#404040";
        opacity: 0.7;
    }

    Grid{
        id:op;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        rows: 2;
        columns: 3;
        rowSpacing: 4;
        columnSpacing: 4;
        z:1

        Button{
            text: "柔化";
            style: btn_style;
            onClicked: {
                busy.running = true;
                processor.process(file_dialog.fileUrl,ImageProcessor.Soften);
            }
        }

        Button{
            text: "灰度";
            style: btn_style;
            onClicked: {
                busy.running = true;
                processor.process(file_dialog.fileUrl,ImageProcessor.Gray);
            }
        }

        Button{
            text: "浮雕";
            style: btn_style;
            onClicked: {
                busy.running = true;
                processor.process(file_dialog.fileUrl,ImageProcessor.Emboss);
            }
        }

        Button{
            text: "黑白";
            style: btn_style;
            onClicked: {
                busy.running = true;
                processor.process(file_dialog.fileUrl,ImageProcessor.Binarize);
            }
        }

        Button{
            text: "底片";
            style: btn_style;
            onClicked: {
                busy.running = true;
                processor.process(file_dialog.fileUrl,ImageProcessor.Negative);
            }
        }

        Button{
            text: "锐化";
            style: btn_style;
            onClicked: {
                busy.running = true;
                processor.process(file_dialog.fileUrl,ImageProcessor.Sharpen);
            }
        }
    }

    Rectangle{
        anchors.left: parent.left;
        anchors.top: op.top;
        anchors.topMargin: -4;
        anchors.bottom: parent.bottom;
        anchors.right: op.right;
        anchors.rightMargin: -4;
        color: "#404040";
        opacity: 0.7;
    }
}
