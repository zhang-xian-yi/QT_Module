import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4


Rectangle{
    id:root;
    width: 480;
    height: 320;

    Grid{
        id:grid_layout;
        anchors.fill: parent;
        rows: 2;
        columns: 2;
        rowSpacing: 4;
        columnSpacing: 4;
        GroupBox{
            title: "只读电器";
            width: 200;
            height: 120;
            ComboBox{
                width:parent.width;
                anchors.top: parent.top;
                anchors.topMargin: 8;
                model: ["TV","CD player","set to top","xxxxxx"];
            }
        }

        GroupBox{
           width: 200;
           height: 120;
           title: "可编辑的水果";
           ComboBox{
               editable: true;
               width: parent.width;
               anchors.top: parent.top;
               anchors.topMargin: 8;

               model: ListModel{
                   ListElement {text:"banana";color:"yellow"}
               }
               onAccepted: {
                   if(count < 4 && find(currentText) === -1)
                   {
                       //追加新的模型
                       model.append({text:editText});
                       currentIndex = find(currentText);
                       //当达到4个选项时候  不可以进行编辑
                       if(count >=4)
                       {
                           editable = false;
                       }
                   }
               }
           }
        }

        GroupBox{
            width: 200;
            height: 120;
            title: "定制风格";
            ComboBox{
                anchors.top: parent.top;
                anchors.topMargin: 8;
                width: parent.width;
                model: ["google","firfox","qq liulanqi"];
                style: ComboBoxStyle{
                    dropDownButtonWidth:20;
                    selectedTextColor: "#FDC725";
                    background: Rectangle{
                        implicitHeight : 24;
                        border.color : (control.hovered || control.pressed) ? "blue":"gray";
                        border.width : control.editable ? 0 : 1;
                        color: (control.hovered || control.pressed) ? "#a0a0a0":"#c0c0c0";
                        Canvas{
                            width: 16;
                            height: 18;
                            anchors.right: parent.right;
                            anchors.rightMargin: 2;
                            anchors.top: parent.top;
                            anchors.topMargin: 1;
                            onPaint: {
                                var ctx = getContext("2d");
                                ctx.save();
                                ctx.strokeStyle = "black";
                                ctx.lineWidth = 2;
                                ctx.beginPath();
                                ctx.moveTo(1,8);
                                ctx.lineTo(8,16);
                                ctx.lineTo(15,8);
                                ctx.stroke();
                                ctx.restore();
                            }
                        }
                    }

                    label: Text{
                        width: control.width -22;
                        height: control.height;
                        verticalAlignment: Text.AlignVCenter;
                        horizontalAlignment: Text.AlignHCenter;
                        text:control.currentText;
                        color: (control.hovered || control.pressed) ? "blue":"black";
                    }


                }
            }
        }

        GroupBox{
            title: "限制输入";
            width: 200;
            height: 120;
            ComboBox{
                anchors.top: parent.top;
                anchors.topMargin: 8;
                width: parent.width;
                editable: true;
                model: ListModel{

                }
                validator: IntValidator{top:12;bottom: 1;}
                onAccepted: {
                    if(count < 12 && find(currentText) === -1)
                    {
                        model.append({text:currentText});
                        currentIndex = find(currentText);
                        if(count >=12)
                        {
                            editable = false;
                        }
                    }
                }
            }
        }



    }


    
    
}


