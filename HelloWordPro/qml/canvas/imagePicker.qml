import QtQuick 2.0
import QtQuick.Window 2.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.3;

Window{
    visible: true;
    width: 480;
    height: 320;
    minimumWidth: 480;
    minimumHeight: 320;
    color: "black";

    onWidthChanged: {
        mask.recalc();
    }
    onHeightChanged: {
        mask.recalc();
    }

    Image {
        id: source_img;
        anchors.fill: parent;
        fillMode: Image.PreserveAspectFit;
        visible: false;
        asynchronous: true;
        onStatusChanged: {
            if(status == Image.Ready)
            {
                console.log("image loaded");
                mask.recalc();
            }
        }
    }
    //文件选择 框
    FileDialog{
        id:file_dialog;
        title: "Please choose an Image File";
        nameFilters: ["Image files {*.jpg *.png *.gif}"];
        onAccepted: {
            source_img.source = file_dialog.fileUrl;
        }
    }

    Canvas{
        id:for_save_canvas;
        width: 128;
        height: 128;
        contextType: "2d";
        visible: false;
        z:2;
        anchors.top: parent.top;
        anchors.right: parent.right;
        anchors.margins: 4;

        property var image_data: null;
        onPaint: {
            if(image_data != null)
            {
                context.drawImage(image_data,0,0);
                mask.recalc();
            }
        }

        function setImageData(data)
        {
            image_data = data;
            requestPaint();
        }
    }

    Canvas{
        id:mask;
        anchors.fill: parent;
        z:1;
        property real w: width;
        property real h: height;
        property real dx: 0;
        property real dy: 0;
        property real dw: 0;
        property real dh: 0;
        property real frameX: 66;
        property real frameY: 66;

        function calc()
        {
            var sw = source_img.sourceSize.width;
            var sh = source_img.sourceSize.height;
            if(sw > 0 && sh >0)
            {
                if(sw <= w && sh <= h)
                {
                    dw =sw;
                    dh = sh;
                }
                else
                {
                    var sRatio = sw / sh;
                    dw = sRatio * h;
                    if( dw > w)
                    {
                        dh = w / sRatio;
                        dw = w;
                    }
                    else
                    {
                        dh = h;
                    }
                }
                dx = (w - dw) /2;
                dy = (h - dh) /2;

            }
        }
        function recalc()
        {
            calc();
            requestPaint();
        }

        function getImageData()
        {
            return context.getImageData(frameX - 64,frameY - 64,128,128);
        }

        onPaint: {
            var ctx = getContext("2d");
            if(dw < 1 || dh <1)
            {
                ctx.fillStyle = "#0000a0";
                ctx.font = "20pt sans-serif";
                ctx.textAlign = "center";
                ctx.fillText("Please Choose an Image File",width/2,height/2);
                return;
            }

            ctx.clearRect(0,0,width,height);
            ctx.drawImage(source_img,dx,dy,dw,dh);
            var xStart = frameX - 66;
            var yStart = frameY - 66;
            ctx.save();

            ctx.fillStyle = "#a0000000";
            ctx.fillRect(0,0,w,yStart);
            var yOffset = yStart + 132;
            ctx.fillRect(0,yOffset,w,h-yOffset);
            ctx.fillRect(0,yStart,xStart,132);

            var xOffset = xStart + 132;
            ctx.fillRect(xOffset,yStart,w-xOffset,132);

            //see through area
            ctx.strokeStyle = "red";
            ctx.fillStyle= "#00000000";
            ctx.lineWidth = 2;
            ctx.beginPath();
            ctx.rect(xStart,yStart,132,132);
            ctx.fill();
            ctx.stroke();
            ctx.closePath();
            ctx.restore();

        }
    }

    MultiPointTouchArea{
        anchors.fill: parent;
        minimumTouchPoints: 1;
        maximumTouchPoints: 1;
        touchPoints: [
            TouchPoint{
                id:point1
            }
        ]
        onUpdated: {
            mask.frameX = point1.x;
            mask.frameY = point1.y;
            mask.requestPaint();
        }

        onReleased: {
            for_save_canvas.setImageData(mask.getImageData());
            actionPanel.visible = true;
        }

        onPressed: {
            actionPanel.visible = false;
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

    RowLayout{
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 20;
        id:actionPanel;
        spacing: 8;
        Button{
            style: btn_style;
            text: "Open";
            onClicked: file_dialog.open();
        }

        Button{
            style: btn_style;
            text:"Save";
            onClicked: {
                for_save_canvas.save("selected.png");
                actionPanel.visible = "false";
            }
        }

        Button{
            style: btn_style;
            text:"Canel";
            onClicked: actionPanel.visible = false;
        }
    }
}

