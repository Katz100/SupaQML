#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QQmlEngine>
#include <QJsonObject>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QEventLoop>
#include <QJsonArray>

class Server : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString projectId READ projectId WRITE setProjectId NOTIFY projectIdChanged FINAL)
    Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged FINAL)
    Q_PROPERTY(QString func READ func WRITE setFunc NOTIFY funcChanged FINAL)
    Q_PROPERTY(QJsonObject parameters READ parameters WRITE setParameters NOTIFY parametersChanged FINAL)
    Q_PROPERTY(bool isUrlValid READ isUrlValid WRITE setIsUrlValid NOTIFY isUrlValidChanged FINAL)
    QML_ELEMENT
public:
    explicit Server(QObject *parent = nullptr);

    Q_INVOKABLE void sendFunctionCall();
    Q_INVOKABLE QJsonArray sendQuery(QString table, QString query);

    QString key() const;
    void setKey(const QString &newKey);

    QJsonObject parameters() const;
    void setParameters(const QJsonObject &newParameters);

    bool isUrlValid() const;
    void setIsUrlValid(bool newIsUrlValid);


    QString func() const;
    void setFunc(const QString &newFunc);

    QString projectId() const;
    void setProjectId(const QString &newProjectId);

signals:

    void messageReceived(QJsonObject message);
    void apiCallFailed(QString message);

    void urlChanged();
    void keyChanged();

    void parametersChanged();

    void isUrlValidChanged();

    void funcChanged();

    void projectIdChanged();

private:
    QUrl m_url;
    QString m_key;
    QJsonObject m_parameters;
    bool m_isUrlValid;
    QString m_func;
    QNetworkAccessManager m_manager;
    QNetworkRequest m_request;
    QString m_projectId;

};

#endif // SERVER_H
