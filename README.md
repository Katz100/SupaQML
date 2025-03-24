# SupaQML

<p>SupaQML is a library that allows you to communicate with your Supabase project using Qt and C++. It provides convenient QML components so you can make direct changes to your user interface without needing to directly interact with Qt's Networking module.</p>

## How To Integrate With Your Qt Project

### In your main CMakeLists.txt
 
```qml
add_subdirectory(SupaQML)
```
### In your QML file

```qml
import SupaQML
```

# Note

The following components require your projects id and anon key. Ensure Row Level Security (RLS) is enabled on your database so users cannot make unauthorized changes to your database.

## SupaAuth

<details open = true>
<summary>Allows you to communicate with Supabase's Authentication API</summary>
  
To learn more about Supabases's authentication endpoint, go to [Supabase Auth](https://github.com/supabase/auth)

```qml
SupaAuth {
  projectId: <Id from your Supabase project>
  key: <The key to your Supabase projects>
  authorization: <Optional parameter that allows you to add a JWT to your request>
  method: <Specify HTTP method. Supports the following enums: POST, PUT, GET>
  endpoint: <Specify the authentication endpoint you with to use. Supports the following enums: SIGNUP, SIGNIN, REFRESH, RECOVER, LOGOUT, USER>
  body: <Specify the body for the endpoint. Accepts a JSON object as a parameter
  requestInProgress: <Read only. Returns true while sendAuth() is in progress, false otherwise>

  Component.onCompleted {
    sendAuth() // Sends an HTTP request using the above parameters to Supabase's authentication API
  }

  onMessageReceived: message => {
    // A signal that is called when sendAuth() is completed. Passes a QVariant that contains a JSON response
    // Adds an additional JSON object, supabase_status for convenience.
  }
}
```
</details>

## SupaSocket
<details open = true>
<summary>Communicate with Supabase Realtime</summary>

Go to [Realtime Protocol](https://supabase.com/docs/guides/realtime/protocol) to learn more about setting up your config.

```qml
SupaSocket {
  projectId: <Id from your Supabase project>
  key: <The key to your Supabase projects>
  authorization: <Optional parameter that allows you to add a JWT to your request>
  sendHeartbeatMessage: <Set to true if you want to keep your connection with Supabase Realtime alive>
  config: <Specify the config for Supabase Realtime. Accepts a JSON object as a parameter>

  Component.onCompleted {
    openConnection() // open a connection to Supabase Realtime with the above parameters.
  }

  onMessageReceived: message => {
    // Returns a QVariant response that contains JSON.
  }
}
```
</details>

## SupaServer
<details open = true>
<summary>Call your PostgreSQL functions</summary>

```qml
SupaServer {
  projectId: <Id from your Supabase project>
  key: <The key to your Supabase projects>
  authorization: <Optional parameter that allows you to add a JWT to your request>
  func: <Specify the PostgreSQL function you would like to call>
  parameters: <Specify the parameters for your function. Accepts a JSON object>

  Component.onCompleted {
   sendFunctionCall() // Calls your PostgreSQL function with the above parameters.
                      // **Note: Has not been tested with every function return type but does accept the return types: table, jsonb, and boolean.
  }

  onMessageReceived: message => {
    // Returns a QVariant response
  }
}
```
</details>
