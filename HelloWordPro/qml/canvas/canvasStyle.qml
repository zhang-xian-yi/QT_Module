import QtQuick 2.0

//定义一个 画布对象
Canvas{
    width: 480;
    height: 320;
    //绘画信号处理器
    onPaint: {
        //定义2d 对象
        var ctx = getContext("2d");
        //设置线条的宽度为2
        ctx.lineWidth = 2;
        //设置线条的颜色为蓝色
        ctx.strokeStyle = "blue";

        var gradient_rect1 = ctx.createLinearGradient(100,80,120,80);
        var gradient_rect2 = ctx.createLinearGradient(100,80,120,80);
        gradient_rect1.addColorStop(0,0,1,1.0);
        gradient_rect.addColorStop(1,0,0,1.0);

        //填充色为红色
        ctx.fillStyle = gradient_rect;
        //开始路径绘画
        ctx.beginPath();
        //画一个矩形
        ctx.rect(100,80,120,80);
        //填充颜色
        ctx.fill();
        ctx.stroke();
    }

}
