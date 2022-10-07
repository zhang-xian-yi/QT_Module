import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Rectangle{
    id:root;
    width: 360;
    height: 300;
    color: "#eeeeee";

    Component
    {
        id:phone_model;
        ListModel
        {
            ListElement
            {
                name:"iPhone 3g";
                cost:"1000";
                menu_facture:"Apple";
            }
            ListElement
            {
                name:"iPhone 4";
                cost:"2000";
                menu_facture:"Apple";
            }
            ListElement
            {
                name:"iPhone 5";
                cost:"3000";
                menu_facture:"Apple";
            }

            ListElement
            {
                name:"B199 5";
                cost:"1999";
                menu_facture:"Apple";
            }
            ListElement
            {
                name:"Mi 25";
                cost:"3150";
                menu_facture:"Apple";
            }
        }
    }



    Component{
        id:header_viewer;
        Item {
            width: parent.width;
            height: 30;

            RowLayout{
                anchors.left: parent.left;
                anchors.verticalCenter: parent.verticalCenter;
                spacing: 8;
                Layout.fillWidth: true;

                Text {
                    text: "Name";
                    font.bold: true;
                    font.pointSize: 24;
                    Layout.preferredWidth: 120;
                }
                Text {
                    text: "Cost";
                    font.bold: true;
                    font.pointSize: 24;
                    Layout.preferredWidth: 120;
                }
                Text {
                    text: "MenuFacture";
                    font.bold: true;
                    font.pointSize: 24;
                    Layout.preferredWidth: 120;
                }
            }
        }
    }

    Component{
        id:foot_view;
        Item
        {
            id:foot_item;
            width: parent.width;
            height:30;
            property alias text: txt.text;
            //定义一个清理信号
            signal clean();
            Text {
                id:txt;
                anchors.left: parent.left;
                anchors.top: parent.top;
                anchors.bottom: parent.bottom;
                width: parent.width;
                height: 30;
                font.italic: true;
                color: "blue";
                verticalAlignment: Text.AlignHCenter;

            }

            Button{
                anchors.right: parent.right;
                anchors.verticalCenter: parent.verticalCenter;
                text: "Clear";
                onClicked: {
                    foot_item.clean();
                }
            }
        }


    }

    Component{
        id:phone_delegate;
        Item {
            id: wrapper;
            width: parent.width;
            height: 30;


            MouseArea{
                anchors.fill: parent;
                hoverEnabled: true;
                onClicked: {
                   //wrapper.ListView.view.currentIndex = index;
                }
                onEntered: {
                   wrapper.ListView.view.currentIndex = index;
                }
                onDoubleClicked: {
                   wrapper.ListView.view.model.remove(index);
                }
            }

            RowLayout{
                anchors.left: parent.left;
                anchors.verticalCenter: parent.verticalCenter;
                spacing: 8;
                Layout.fillWidth: true;

                Text {
                    id: coll;
                    text: name;
                    color: wrapper.ListView.isCurrentItem ? "red":"blue";
                    font.pointSize: wrapper.ListView.isCurrentItem? 22:18;
                    Layout.preferredWidth: 120;
                }
                Text {
                    text: cost;
                    color: wrapper.ListView.isCurrentItem ? "red":"blue";
                    font.pointSize: wrapper.ListView.isCurrentItem? 22:18;
                    Layout.preferredWidth: 120;
                }
                Text {
                    text: menu_facture;
                    color: wrapper.ListView.isCurrentItem ? "red":"blue";
                    font.pointSize: wrapper.ListView.isCurrentItem? 22:18;
                    Layout.preferredWidth: 120;
                }
            }
        }
    }


    ListView{
        id:list_view;
        anchors.fill: parent;
        delegate: phone_delegate;
        model: phone_model.createObject(list_view);
        header: header_viewer;
        footer: foot_view;
        focus: true;
        highlight: Rectangle{
            color: "lightblue";
        }

        onCurrentIndexChanged: {
            //list view 的下标是从0 开始的
            if(list_view.currentIndex >= 0)
            {
                var  data = list_view.model.get(list_view.currentIndex);
                list_view.footerItem.text = data.name + ",  "+data.cost+",  "+data.menu_facture;
            }
            else
            {
                list_view.footerItem.text = "";
            }
        }

        Component.onCompleted: {
            list_view.footerItem.clean.connect(list_view.model.clear);
        }
    }

}
