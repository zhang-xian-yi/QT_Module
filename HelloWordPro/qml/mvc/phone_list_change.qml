import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Rectangle{
    id:root;
    width: 360;
    height: 300;
    color: "#eeeeee";
    Component{
        id:phone_model;
        ListModel{
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
                    Layout.fillWidth: true;
                }
            }
        }
    }

    Component{
        id:footer_view;
        Item
        {
            id:foot_item;
            width: parent.width;
            height:30;
            property alias text: txt.text;
            //定义一个清理信号
            signal clean();
            signal add();
            signal insert();
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
                id:clear_btn;
                anchors.right: parent.right;
                anchors.verticalCenter: parent.verticalCenter;
                text: "Clear";
                onClicked: {
                    foot_item.clean();
                }
            }

            Button{
                id:add_btn;
                anchors.right: clear_btn.left;
                anchors.rightMargin: 8;
                anchors.verticalCenter: parent.verticalCenter;
                text: "Add";
                onClicked: {
                    foot_item.add();
                }
            }
            Button{
                id:insert_btn;
                anchors.right: add_btn.left;
                anchors.rightMargin: 8;
                anchors.verticalCenter: parent.verticalCenter;
                text: "Insert";
                onClicked: {
                    foot_item.insert();
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
                    mouse.accepted = true;
                }
                onDoubleClicked: {
                    wrapper.ListView.view.model.remove(index);
                    mouse.accepted = true;
                }
            }

            RowLayout{
                anchors.left: parent.left;
                anchors.verticalCenter: parent.verticalCenter;
                spacing: 8;
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
                    Layout.fillWidth: true;
                }
            }
        }
    }

    ListView{
        id:list_view;
        anchors.fill: parent;
        delegate: phone_delegate;
        header: header_viewer;
        footer: footer_view;
        focus: true;
        highlight: Rectangle{
            color: "lightblue";
        }
        model:phone_model.createObject(list_view);
        populate: Transition {
            ParallelAnimation{
                NumberAnimation{
                    property: "opacity";
                    from:0.0;
                    to:1.0;
                    duration: 2000;
                }
            }
        }
        remove: Transition {
            ParallelAnimation{
                NumberAnimation{
                    property: "opacity";
                    from:1.0;
                    to:0;
                    duration: 1000;
                }
                NumberAnimation{
                    property: "y";
                    to:0;
                    duration: 1000;
                }
            }
        }
        add:Transition {
            ParallelAnimation{
                NumberAnimation{
                    property: "opacity";
                    from:0.0;
                    to:1.0;
                    duration: 1000;
                }
            }
        }

        onCurrentIndexChanged: {
            if(list_view.currentIndex >= 0)
            {
                var data = list_view.model.get(list_view.currentIndex);
                list_view.footerItem.text = data.name + " ,"+data.cost+" ,"+data.menu_facture;
            }
            else
            {
                list_view.footerItem.text = "";
            }
        }
        function addOne()
        {
            model.append({
                "name":"Max 3",
                "cost":"1799",
                "menu_facture":"Meizu"
           });
        }

        function insertOne()
        {
            model.insert(Math.round(Math.random() * model.count),
                         {
                             "name":"Thinkpad3",
                             "cost":"666",
                             "menu_facture":"vivi"
                         });
        }

        Component.onCompleted: {
            list_view.footerItem.clean.connect(list_view.model.clear);
            list_view.footerItem.add.connect(list_view.addOne);
            list_view.footerItem.insert.connect(list_view.insertOne);
        }
    }
}
