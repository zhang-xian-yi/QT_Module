import QtQuick 2.0

Rectangle{
    width: 300
    height: 200;
    Item {
        id: gradientGroup
        Rectangle{
            id:rect1
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.top: parent.top
            anchors.topMargin: 20
            width: 120
            height: 120
            gradient: Gradient{
                GradientStop{position: 0.0;color: "#ff0000"}
                GradientStop{position: 1.0;color: "#00ff00"}
            }

            Rectangle{
                anchors.centerIn: parent
                width: 40
                height: 40
                border.width: 6
                border.color: "black"
                color: "blue"
            }

        }
        Rectangle{
            anchors.left: rect1.right
            anchors.leftMargin: 20
            anchors.top: rect1.top
            width: 120
            height: 120
            //旋转九十度
            rotation: 90
            //渐变效果
            gradient: Gradient{
                GradientStop{position: 0.0;color: "#ff0000"}
                GradientStop{position: 1.0;color: "#00ff00"}
            }
        }
    }

    Component.onCompleted: {
        console.log("visible children :",gradientGroup.visibleChildren.length);
        console.log("children :",gradientGroup.children.length);
        for(var i = 0;i<gradientGroup.children.length;++i)
        {
            console.log("child ",i,"  x = ",gradientGroup.children[i].x);
        }
    }
}
