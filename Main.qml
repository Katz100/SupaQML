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
        sendHeartbeatMessage: true
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
        func: "testget2"
        projectId: "hvfufeffqgblugookder"
        authorization: "eyJhbGciOiJIUzI1NiIsImtpZCI6InZWM0pvcVdnbVhPQ1dGVzQiLCJ0eXAiOiJKV1QifQ.eyJpc3MiOiJodHRwczovL2h2ZnVmZWZmcWdibHVnb29rZGVyLnN1cGFiYXNlLmNvL2F1dGgvdjEiLCJzdWIiOiIzN2Q0OThhMS0zMTIzLTQ4MmYtYjlhMS1mNzU0Yzk0YjRmMjciLCJhdWQiOiJhdXRoZW50aWNhdGVkIiwiZXhwIjoxNzMyODM1NjYxLCJpYXQiOjE3MzI4MzIwNjEsImVtYWlsIjoiY29keS5ob3BraW5zMTA4QGdtYWlsLmNvbSIsInBob25lIjoiIiwiYXBwX21ldGFkYXRhIjp7InByb3ZpZGVyIjoiZW1haWwiLCJwcm92aWRlcnMiOlsiZW1haWwiXX0sInVzZXJfbWV0YWRhdGEiOnsiZW1haWwiOiJjb2R5LmhvcGtpbnMxMDhAZ21haWwuY29tIiwiZW1haWxfdmVyaWZpZWQiOmZhbHNlLCJwaG9uZV92ZXJpZmllZCI6ZmFsc2UsInN1YiI6IjM3ZDQ5OGExLTMxMjMtNDgyZi1iOWExLWY3NTRjOTRiNGYyNyJ9LCJyb2xlIjoiYXV0aGVudGljYXRlZCIsImFhbCI6ImFhbDEiLCJhbXIiOlt7Im1ldGhvZCI6InBhc3N3b3JkIiwidGltZXN0YW1wIjoxNzMyODMyMDYxfV0sInNlc3Npb25faWQiOiJjMWVmYWUzOS00ODI0LTQzOWYtYmNlZS1lNWQ2OWU0MThhOGYiLCJpc19hbm9ueW1vdXMiOmZhbHNlfQ.fEUH91VetBmFJ2HkcU-t2eYDeI5JuV6CR2Z9KLUXBWU"
        key: "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Imh2ZnVmZWZmcWdibHVnb29rZGVyIiwicm9sZSI6ImFub24iLCJpYXQiOjE3MzE0NTA2NjcsImV4cCI6MjA0NzAyNjY2N30._elTtX-VMR54gcHfn9rO6jm4E3etdXN0Dp25MZu_YYs"

        parameters: {
            "u_id": "0fb80717-b577-470d-be36-e6ee4720ded6"
            }

        Component.onCompleted: {
            var ob = sendQuery("test", "select=name,id")
            for (let i = 0; i < ob.length; i++)
            {
                lm.insert(i, {"id": ob[i].id, "name": ob[i].name})
            }
            txt.text = sendFunctionCall().name

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
