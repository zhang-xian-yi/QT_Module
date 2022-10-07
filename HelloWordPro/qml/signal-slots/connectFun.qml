import QtQuick 2.0

Rectangle{
    id:root;
    width: 480;
    height: 320;

    Rectangle{
        id:relay;
        width: parent.width * 0.5;
        height: parent.height;

        anchors.left: parent.left;
        color: "blue";


        signal message_recv(string person,string notic);
        Component.onCompleted: {
            relay.message_recv.connect(send2Email);
            relay.message_recv.connect(send2Tel);
            relay.message_recv.connect(send2Post);
            message_recv("zhangxianyi","happy birthday");
        }

        function send2Email(person,notice){
            console.log("send to email "+person+"  ------- notice: "+notice);
        }
        function send2Tel(person,notice){
            console.log("send to telphone "+person+"  ------- notice: "+notice);
        }
        function send2Post(person,notice){
            console.log("send to post "+person+"  ------- notice: "+notice);
        }

    }

    Rectangle{
        id:forword;
        width: parent.width * 0.4;
        height: parent.height;

        color: "red";

        anchors.left: relay.right;
        anchors.leftMargin: 4;

        signal send();
        onSend: {
            console.log("sned clicked");
        }

        MouseArea{
            id:mArea;
            anchors.fill: parent;
            onClicked: {
                console.log("Mouse area clicked");
            }
        }

        Component.onCompleted: {
            mArea.clicked.connect(sned);
        }
    }

}
