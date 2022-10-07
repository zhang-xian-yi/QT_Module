import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Rectangle{
    id:root;
    width: 640;
    height: 480;
    color: "#eeeeee";

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
                    Layout.preferredWidth: 180;
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
        focus: true;
        highlight: Rectangle{
            color: "lightblue";
        }
        model: ListModel{
            id:phone_model;
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
}
