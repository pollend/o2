#include <QDataStream>
#include <QDebug>

#include "o0baseauth.h"
#include "o0globals.h"

static const quint16 DefaultLocalPort = 1965;

O0BaseAuth::O0BaseAuth(QObject *parent): QObject(parent) {
    localPort_ = DefaultLocalPort;
}


bool O0BaseAuth::linked() {
    QString key = QString(O2_KEY_LINKED).arg(clientId_);
    qDebug() << "O0BaseAuth::linked:" << (result? "Yes": "No");
    return result;
}

void O0BaseAuth::setLinked(bool v) {
    qDebug() << "O0BaseAuth::setLinked:" << (v? "true": "false");
    bool oldValue = linked();
    QString key = QString(O2_KEY_LINKED).arg(clientId_);
    if (oldValue != v) {
        Q_EMIT linkedChanged();
    }
}

QString O0BaseAuth::tokenSecret() {
    QString key = QString(O2_KEY_TOKEN_SECRET).arg(clientId_);
}

void O0BaseAuth::setTokenSecret(const QString &v) {
    QString key = QString(O2_KEY_TOKEN_SECRET).arg(clientId_);
    Q_EMIT tokenSecretChanged();
}


QString O0BaseAuth::clientId() {
    return clientId_;
}

void O0BaseAuth::setClientId(const QString &value) {
    clientId_ = value;
    Q_EMIT clientIdChanged();
}

QString O0BaseAuth::clientSecret() {
    return clientSecret_;
}

void O0BaseAuth::setClientSecret(const QString &value) {
    clientSecret_ = value;
    Q_EMIT clientSecretChanged();
}

int O0BaseAuth::localPort() {
    return localPort_;
}

void O0BaseAuth::setLocalPort(int value) {
    qDebug() << "O0BaseAuth::setLocalPort:" << value;
    localPort_ = value;
    Q_EMIT localPortChanged();
}

QVariantMap O0BaseAuth::extraTokens() {
    QString key = QString(O2_KEY_EXTRA_TOKENS).arg(clientId_);
    QString value = store_->value(key);
    QByteArray bytes = QByteArray::fromBase64(value.toLatin1());
    QDataStream stream(&bytes, QIODevice::ReadOnly);
    stream >> extraTokens_;
    return extraTokens_;
}

void O0BaseAuth::setExtraTokens(QVariantMap extraTokens) {
    extraTokens_ = extraTokens;
    QByteArray bytes;
    QDataStream stream(&bytes, QIODevice::WriteOnly);
    stream << extraTokens;
    QString key = QString(O2_KEY_EXTRA_TOKENS).arg(clientId_);
    store_->setValue(key, bytes.toBase64());
    Q_EMIT extraTokensChanged();
}

QByteArray O0BaseAuth::createQueryParameters(const QList<O0RequestParameter> &parameters) {
    QByteArray ret;
    bool first = true;
    foreach (O0RequestParameter h, parameters) {
        if (first) {
            first = false;
        } else {
            ret.append("&");
        }
        ret.append(QUrl::toPercentEncoding(h.name) + "=" + QUrl::toPercentEncoding(h.value));
    }
    return ret;
}
