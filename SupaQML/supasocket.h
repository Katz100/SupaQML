#ifndef SUPASOCKET_H
#define SUPASOCKET_H

#include <QObject>
#include <QQmlEngine>
#include <QWebSocket>
#include <QJsonObject>

class SupaSocket : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString projectId READ projectId WRITE setProjectId NOTIFY projectIdChanged FINAL)
    Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged FINAL)
    Q_PROPERTY(QJsonObject payload READ payload WRITE setPayload NOTIFY payloadChanged FINAL)
    QML_ELEMENT
public:
    explicit SupaSocket(QObject *parent = nullptr);
    ~SupaSocket();

    Q_INVOKABLE void openConnection();


    QString projectId() const;
    void setProjectId(const QString &newProjectId);

    QString key() const;
    void setKey(const QString &newKey);

    QJsonObject payload() const;
    void setPayload(const QJsonObject &newPayload);

signals:
    void projectIdChanged();
    void keyChanged();

    void payloadChanged();

private:
    QString m_projectId;
    QString m_key;
    QJsonObject m_payload;
    QWebSocket m_webSocket;

};

#endif // SUPASOCKET_H
