import QtQuick
import QmlSupabaseIntegration

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")



    Server {
        id: server
        func: "testget"
        projectId: "hvfufeffqgblugookder"
        key: "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Imh2ZnVmZWZmcWdibHVnb29rZGVyIiwicm9sZSI6ImFub24iLCJpYXQiOjE3MzE0NTA2NjcsImV4cCI6MjA0NzAyNjY2N30._elTtX-VMR54gcHfn9rO6jm4E3etdXN0Dp25MZu_YYs"

        parameters: {
            "u_id": 9,
            "u_name": "john"
            }

        Component.onCompleted: sendFunctionCall()

        onMessageReceived: {
            console.log(message["name"])
        }

        onApiCallFailed: {
            console.log(message)
        }
    }

}
