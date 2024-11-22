<h1>How To Use</h1>
<p>In your main CMakeLists.txt:</p>
<pre><code>add_subdirectory(SupaQML)</code></pre>
<p>In your QML file</p>
<pre><code>import SupaQML</code></pre>
<h1>Supabase Function Caller</h1>
<details>
  <p>Lets you call your postgres functions using Supabase's api endpoints</p>
  <h1>List of properties</h1>
  <ul>
    <li>projectId</li>
    <li>key</li>
    <li>func</li>
    <li>parameter</li>
    <li>isUrlValid</li>
  </ul>
  <h3>Example using the following postgres function</h3>
  <pre><code>CREATE OR REPLACE FUNCTION testGet(u_id integer, u_name text) 
RETURNS jsonb AS $$
SELECT jsonb_build_object('name', name)
FROM test
WHERE test.id = u_id;
$$ LANGUAGE sql;</code></pre>
  <h3>Define the following Server component</h3>
 <pre><code>
   Server {
    id: server
    func: "testget"
    projectId: "your project id"
    key: "your project key"

    parameters: {
        "u_id": 9,
        "u_name": "john"
    }

    Component.onCompleted: sendFunctionCall()

    onMessageReceived: {
        console.log(message["name"]);
    }

    onApiCallFailed: {
        console.log(message);
    }}
</pre></code>
  <p>Insert your function parameters into the 'parameters' property as a JSON value. Call sendFunctionCall() to make a request to Supabase's API. The signals messageReceived and apiCalledFailed will return the API's response</p>
</details>
<h1>sendQuery(QString table, QString query)</h1>
<details>
  <p>Performs a query on your table via PostgREST. Returns a response as a <code>QJsonArray</code>.</p>
  <p>For for information on how to structure your queries, visit https://docs.postgrest.org/en/v12/references/api/tables_views.html</p>
</details>
                                
