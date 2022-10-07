import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.0

Rectangle{
    width: 480
    height: 320

    Component{
        id:btnStyle
        ButtonStyle{
            background: Rectangle{
                implicitWidth: 70
                implicitHeight: 20
                color: "red"
                border.width: control.pressed ? 2:1
                border.color: {control.hover || control.pressed ? "green":"#888888"}

            }
        }

    }

    Button{
        id:btn1

    }
}
