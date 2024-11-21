import QtQuick
import SupaQML

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")



    SupaServer {
        id: server
        func: "testget"
        projectId: "hvfufeffqgblugookder"
        key: "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Imh2ZnVmZWZmcWdibHVnb29rZGVyIiwicm9sZSI6ImFub24iLCJpYXQiOjE3MzE0NTA2NjcsImV4cCI6MjA0NzAyNjY2N30._elTtX-VMR54gcHfn9rO6jm4E3etdXN0Dp25MZu_YYs"

        parameters: {
            "u_id": 9
            }

        Component.onCompleted: {
            sendFunctionCall()
            var message2 = sendQuery("test", "select=name")
            //console.log(JSON.stringify(message2))
            for(var i = 0; i < message2.length; i++) {
                console.log(message2[i].name)
            }
        }

        onMessageReceived: {
            txt.text = "Hello %1.".arg(message["name"])
        }

        onApiCallFailed: {
            console.log(message)
        }
    }

    Text {
        id: txt
        anchors.centerIn: parent
    }
}
