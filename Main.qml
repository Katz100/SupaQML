import QtQuick
import SupaQML

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ListModel {
        id: lm
    }

    SupaSocket {
        id: socket
        projectId: "hvfufeffqgblugookder"
        key: "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Imh2ZnVmZWZmcWdibHVnb29rZGVyIiwicm9sZSI6ImFub24iLCJpYXQiOjE3MzE0NTA2NjcsImV4cCI6MjA0NzAyNjY2N30._elTtX-VMR54gcHfn9rO6jm4E3etdXN0Dp25MZu_YYs"
        Component.onCompleted: {
            socket.openConnection()
        }
    }

    SupaAuth {
        id: auth
        projectId: "hvfufeffqgblugookder"
        key: "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Imh2ZnVmZWZmcWdibHVnb29rZGVyIiwicm9sZSI6ImFub24iLCJpYXQiOjE3MzE0NTA2NjcsImV4cCI6MjA0NzAyNjY2N30._elTtX-VMR54gcHfn9rO6jm4E3etdXN0Dp25MZu_YYs"
        method: SupaAuth.POST
        body: {
            "email": "cody.hopkins108@gmail.com",
            "password": "mypassword"
        }
        endpoint: SupaAuth.SIGNIN

        Component.onCompleted: {
            console.log(sendAuth().access_token)
        }
    }

    SupaServer {
        id: server
        func: "testget"
        projectId: "hvfufeffqgblugookder"
        key: "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Imh2ZnVmZWZmcWdibHVnb29rZGVyIiwicm9sZSI6ImFub24iLCJpYXQiOjE3MzE0NTA2NjcsImV4cCI6MjA0NzAyNjY2N30._elTtX-VMR54gcHfn9rO6jm4E3etdXN0Dp25MZu_YYs"

        parameters: {
            "u_id": 9
            }

        Component.onCompleted: {
            txt.text = sendFunctionCall().name
            var ob = sendQuery("test", "select=name,id")
            for (let i = 0; i < ob.length; i++)
            {
                lm.insert(i, {"id": ob[i].id, "name": ob[i].name})
            }
        }



        onApiCallFailed: {
            console.log(message)
        }
    }

    Text {
        id: txt
        anchors.centerIn: parent
    }

    ListView
    {
        id: lv
        anchors.fill: parent
        model: lm
        delegate: Text {
            text: model.id + " " + model.name
        }
    }
}
