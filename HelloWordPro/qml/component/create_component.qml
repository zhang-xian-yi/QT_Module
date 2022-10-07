import QtQuick 2.0
import QtQuick.Controls 2.4

Rectangle{
    id:root_item;
    width: 480;
    height: 320;
    property int count: 0;
    property Component component: null;
    property var comObjs: [];
    Text {
        id: txt_show;
        text: qsTr("Hello Woord!!");
        anchors.centerIn: parent;
        font.pointSize: 32;
    }

    Button{
        id:add;
        text: "add";
        anchors.left: parent.left;
        anchors.leftMargin: 5;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 5;
        onClicked: {
            createComponent(Qt.rgba(Math.random() % 255 ,Math.random() % 255,Math.random() % 255,1));
        }
    }
    Button{
        id:del;
        text: "del";
        anchors.right : parent.right;
        anchors.rightMargin: 5;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 5;
        onClicked: {
            if(root_item.comObjs.length > 0)
            {
                root_item.comObjs.pop().destroy();
                root_item.count -- ;
            }
        }
    }

    function changeTextColor(clr)
    {
         txt_show.color = clr;
    }

    function createComponent(clr)
    {
        //创建一个组件对象
        if(root_item.component === null)
        {
            root_item.component = Qt.createComponent("ColorClicker.qml");
        }
        //生成组件对象的一个实例
        var color_clicker_component;
        if(root_item.component.status == Component.Ready)
        {
            //通过组件对象 创建该组件的一个实例
            color_clicker_component = root_item.component.createObject(root_item,{"x":root_item.count * 55,"color":clr,"y":10});
            //为新创建的组件实例的信号 进行连接
            color_clicker_component.hover_signal.connect(changeTextColor);
            //保存在数组中
            comObjs.push(color_clicker_component);
        }
        root_item.count ++;
    }


}
