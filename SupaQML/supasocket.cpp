#include "supasocket.h"

SupaSocket::SupaSocket(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, [this](){
        if (m_sendHeartbeatMessage && m_webSocket.state() == QAbstractSocket::ConnectedState)
        {
            QJsonObject payload;
            payload["event"] = "heartbeat";
            payload["topic"] = "phoenix";
            QJsonObject empty;
            payload["payload"] = empty;
            payload["ref"] = QString::number(QDateTime::currentMSecsSinceEpoch());
            sendTextMessage(payload);
        }

    });
    timer->start(30000);
    QObject::connect(&m_webSocket, &QWebSocket::connected, this, [this](){
        QJsonObject payload;
        payload["event"] = "phx_join";
        payload["topic"] = "realtime:public:test"; // Specify schema and table in the topic
        payload["ref"] = "1";

        // Additional configuration if needed
        QJsonObject config;
        config["schema"] = "public";
        config["table"] = "test";

        payload["payload"] = config;

        // Send the constructed JSON payload as a text message
        sendTextMessage(payload);
    });

    QObject::connect(&m_webSocket, &QWebSocket::disconnected, this, [](){
        qDebug() << "disconnected";
    });

    QObject::connect(&m_webSocket, &QWebSocket::errorOccurred, this, [](QAbstractSocket::SocketError error){
        qDebug() << error;
    });

    QObject::connect(&m_webSocket, &QWebSocket::textMessageReceived, this, [](const QString& message){
        qDebug() << message;
    });

    QObject::connect(&m_webSocket, &QWebSocket::stateChanged, this, [](QAbstractSocket::SocketState state){
        qDebug() << state;
    });

    QObject::connect(&m_webSocket, &QWebSocket::binaryMessageReceived, this, [](const QByteArray message){
        qDebug() << message;
    });
}
SupaSocket::~SupaSocket()
{
    m_webSocket.close();
}

void SupaSocket::openConnection()
{
    QUrl url = QString("wss://%1.supabase.co/realtime/v1/websocket?apikey=%2&log_level=info&vsn=1.0.0").arg(m_projectId, m_key);
    m_webSocket.open(url);
}

void SupaSocket::sendTextMessage(QJsonObject payload)
{
    QJsonDocument doc(payload);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    qDebug() << doc;
    m_webSocket.sendTextMessage(strJson);
}

QString SupaSocket::projectId() const
{
    return m_projectId;
}

void SupaSocket::setProjectId(const QString &newProjectId)
{
    if (m_projectId == newProjectId)
        return;
    m_projectId = newProjectId;
    emit projectIdChanged();
}

QString SupaSocket::key() const
{
    return m_key;
}

void SupaSocket::setKey(const QString &newKey)
{
    if (m_key == newKey)
        return;
    m_key = newKey;
    emit keyChanged();
}

QJsonObject SupaSocket::payload() const
{
    return m_payload;
}

void SupaSocket::setPayload(const QJsonObject &newPayload)
{
    if (m_payload == newPayload)
        return;
    m_payload = newPayload;
    emit payloadChanged();
}

bool SupaSocket::sendHeartbeatMessage() const
{
    return m_sendHeartbeatMessage;
}

void SupaSocket::setSendHeartbeatMessage(bool newSendHeartbeatMessage)
{
    if (m_sendHeartbeatMessage == newSendHeartbeatMessage)
        return;
    m_sendHeartbeatMessage = newSendHeartbeatMessage;
    emit sendHeartbeatMessageChanged();
}
