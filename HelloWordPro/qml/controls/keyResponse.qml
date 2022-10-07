import QtQuick 2.0

Rectangle{
    width: 300
    height: 200

    focus: true
    color: "#c0c0c0"
    Keys.enabled: true

    Keys.onEscapePressed: Qt.quit();
    Keys.onBackPressed: Qt.quit();
    Keys.onPressed: {
        switch(event.key)
        {
            case Qt.Key_0:
            case Qt.Key_1:
            case Qt.Key_2:
            case Qt.Key_3:
            case Qt.Key_4:
            {
                event.accept=true
                keyViewText.text = event.key - Qt.Key_0
                break;
            }
        }

    }

    Text {
        id: keyViewText
        text: qsTr("show key num")
        font.bold: true
        font.pixelSize: 24
        anchors.centerIn: parent
    }
}
