
/*
import QtQuick 2.0
import QtQuick.Controls 1.4

//简单版本 的tabview
Rectangle{
    width: 490;
    height: 320;
    id:root;

    Component{
        id:tab_content;
        Rectangle{
            implicitWidth: 100;
            implicitHeight: 80;
            anchors.fill: parent;
            color: Qt.rgba(Math.random(),Math.random(),Math.random(),1);
        }
    }

    Button{
        id:add_tab;
        text: "add tab";
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.margins: 3;
        onClicked: {
            tab_view.addTab("tab_"+tab_view.count+1,tab_content);
        }
    }

    TabView{
        id:tab_view;
        anchors.top: add_tab.bottom;
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;
    }
}
*/



import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

Rectangle{
    id:root;
    width: 480;
    height: 320;
    color: "lightgray";

    Rectangle{
        id:index;
        implicitWidth: parent.width;
        implicitHeight: parent.height * 0.2;
        color: Qt.rgba(Math.random(),Math.random(),Math.random(),1);
    }

    Rectangle{
        id:view;
        anchors.top: index.bottom;
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        anchors.right: parent.right;
        //以当前路径 为图片相对路径的起始点
        property var icons:["../../appfile/images/qmlicons/drink.png",
                            "../../appfile/images/qmlicons/meat.png",
                            "../../appfile/images/qmlicons/noodles.png",
                            "../../appfile/images/qmlicons/soup.png",
                            "../../appfile/images/qmlicons/vegetable.png"];
        //color: "red";
        Component.onCompleted: {
            order_meal_view.addTab("酒水",tab_content);
            order_meal_view.addTab("肉食",tab_content);
            order_meal_view.addTab("面食",tab_content);
            order_meal_view.addTab("汤类",tab_content);
            order_meal_view.addTab("蔬菜",tab_content);
        }

        Component{
            id:tab_content;
            Rectangle{
                implicitWidth: 100;
                implicitHeight: 80;
                anchors.fill: parent;
                color: Qt.rgba(Math.random(),Math.random(),Math.random(),1);
            }
        }

        TabView{
            id:order_meal_view;
            anchors.fill: parent;
            style: TabViewStyle{
                tab: Item{
                    //指定 初始宽度 未明确指定宽度或者高度的时候   图片和文本 有时候不能适应（无法显示）   自适应大小的操作
                    implicitWidth: Math.max((tab_text.width + tab_image.width),(order_meal_view.width / control.count));
                    implicitHeight: 48;
                    Rectangle{
                        //当前标签的索引 的宽度变化
                        width: (styleData.index < control.count ) ? (parent.width - 4): (parent.width);
                        height: parent.height -4;
                        anchors.top: parent.top;
                        anchors.left: parent.left;
                        anchors.leftMargin: 1;
                        visible: styleData.selected;
                        gradient: Gradient{
                            GradientStop{position: 0.0;color: "#606060";}
                            GradientStop{position: 0.5;color: "#c0c0c0";}
                            GradientStop{position: 1.0;color: "#a0a0a0";}
                        }
                    }
                    Rectangle{
                        width: 2;
                        height: parent.height -2;
                        anchors.top: parent.top;
                        anchors.right: parent.right;
                        visible: styleData.index < control.count -1;
                        gradient: Gradient{
                            GradientStop{position: 0.0;color: "#404040";}
                            GradientStop{position: 0.5;color: "#707070";}
                            GradientStop{position: 1.0;color: "#404040";}
                        }
                    }
                    RowLayout{
                        implicitWidth: Math.max(tab_text.width + 8,72);
                        //width: parent.width / styleData.count;
                        height: 48;
                        anchors.centerIn: parent;
                        z:1;
                        Image {
                            id:tab_image;
                            width: 48;
                            height: 48;
                            anchors.left: parent.left;
                            anchors.top: parent.top;
                            anchors.bottom: parent.bottom;

                            fillMode: Image.PreserveAspectFit;
                            asynchronous: true;
                            cache: false;
                            source: view.icons[styleData.index % 5];
                            z:2;
                        }
                        Text {
                            id: tab_text;
                            text: styleData.title;
                            z:3;
                            color: styleData.selected ? "blue":(styleData.hovered ? "green":"white");
                        }
                    }
                }
                tabBar: Rectangle{
                    height: 48;
                    gradient: Gradient{
                        GradientStop{position: 0.0;color: "#484848";}
                        GradientStop{position: 0.3;color: "#787878";}
                        GradientStop{position: 1.0;color: "#a0a0a0";}
                    }
                    Rectangle{
                        width: parent.width;
                        height: 4;
                        anchors.bottom: parent.bottom;
                        border.width: 2;
                        border.color: "#c7c7c7";
                    }
                }
            }


        }
    }


}
