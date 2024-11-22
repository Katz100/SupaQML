#include "supasocket.h"

SupaSocket::SupaSocket(QObject *parent)
    : QObject{parent}
{
    QObject::connect(&m_webSocket, &QWebSocket::connected, this, [](){
        qDebug() << "connected";
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
}
SupaSocket::~SupaSocket()
{
    m_webSocket.close();
}

void SupaSocket::openConnection()
{
    QUrl url = QString("wss://%1.supabase.co/realtime/v1/websockets?apikey=%2&log_level=info&vsn=1.0.0").arg(m_projectId, m_key);
    qDebug() << url;
    m_webSocket.open(url);
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
