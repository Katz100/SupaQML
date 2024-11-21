#include "server.h"

Server::Server(QObject *parent)
    : QObject{parent}
{}

QString Server::key() const
{
    return m_key;
}

void Server::setKey(const QString &newKey)
{
    if (m_key == newKey)
        return;
    m_key = newKey;
    emit keyChanged();
}

QJsonObject Server::parameters() const
{
    return m_parameters;
}

void Server::setParameters(const QJsonObject &newParameters)
{
    if (m_parameters == newParameters)
        return;
    m_parameters = newParameters;
    emit parametersChanged();
}

bool Server::isUrlValid() const
{
    return m_isUrlValid;
}

void Server::setIsUrlValid(bool newIsUrlValid)
{
    if (m_isUrlValid == newIsUrlValid)
        return;
    m_isUrlValid = newIsUrlValid;
    emit isUrlValidChanged();
}

void Server::sendFunctionCall()
{
    QString new_url = QString("https://%1.supabase.co/rest/v1/rpc").arg(m_projectId) + "/" + m_func;
    m_request.setRawHeader("apikey", m_key.toUtf8());
    m_request.setUrl(QUrl(new_url));
    QJsonDocument doc(m_parameters);
    QByteArray data = doc.toJson(QJsonDocument::Compact);

    QNetworkReply* reply = m_manager.post(m_request, data);

    QEventLoop eventLoop;
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
    if (reply->error() == QNetworkReply::NoError)
    {
        setIsUrlValid(true);
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        emit messageReceived(jsonDoc.object());
        reply->deleteLater();
    }
    else {
        setIsUrlValid(false);
        emit apiCallFailed(reply->errorString());
    }
}

QJsonArray Server::sendQuery(QString table, QString query)
{
    QString new_url = QString("https://%1.supabase.co/rest/v1/%2?%3").arg(m_projectId, table, query);
    qDebug() << new_url;
    m_request.setRawHeader("apikey", m_key.toUtf8());
    m_request.setUrl(QUrl(new_url));

    QNetworkReply* reply = m_manager.get(m_request);

    QEventLoop eventLoop;
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        return jsonDoc.array();
    }
    else
    {
        return QJsonArray{{"Error, reply not sent"}};
    }

    return QJsonArray();
}


QString Server::func() const
{
    return m_func;
}

void Server::setFunc(const QString &newFunc)
{
    if (m_func == newFunc)
        return;
    m_func = newFunc;
    emit funcChanged();
}

QString Server::projectId() const
{
    return m_projectId;
}

void Server::setProjectId(const QString &newProjectId)
{
    if (m_projectId == newProjectId)
        return;
    m_projectId = newProjectId;
    emit projectIdChanged();
}
