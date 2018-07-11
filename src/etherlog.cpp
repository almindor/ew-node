#include "etherlog.h"
#include <QDebug>
#include <QSettings>

namespace Etherwall {

    static EtherLog* sLog = NULL;

    EtherLog::EtherLog() :
        QAbstractListModel(0), fList()
    {
        sLog = this;
        const QSettings settings;
        fLogLevel = (LogSeverity)settings.value("program/loglevel", LS_Info).toInt();
    }

    QHash<int, QByteArray> EtherLog::roleNames() const {
        QHash<int, QByteArray> roles;
        roles[MsgRole] = "msg";
        roles[DateRole] = "date";
        roles[SeverityRole] = "severity";

        return roles;
    }

    int EtherLog::rowCount(const QModelIndex & parent __attribute__ ((unused))) const {
        return fList.length();
    }

    QVariant EtherLog::data(const QModelIndex & index, int role) const {
        return fList.at(index.row()).value(role);
    }

    const QString EtherLog::getContents() const {
        QString text;

        foreach ( const LogInfo info, fList ) {
            text += (info.value(MsgRole).toString() + QString("\n"));
        }

        return text;
    }

    void EtherLog::logMsg(const QString &msg, LogSeverity sev) {
        sLog->log(msg, sev);
    }

    void EtherLog::log(QString msg, int sev) {
        if ( sev < fLogLevel ) {
            return; // skip due to severity setting
        }

        if ( msg.contains("personal_unlockAccount") || msg.contains("personal_signAndSendTransaction") ) {
            msg = "account content *REDACTED*";
        }

        if ( sev >= LS_Warning ) {
            qDebug() << msg << "\n";
        }

        beginInsertRows(QModelIndex(), 0, 0);
        fList.insert(0, LogInfo(msg, (LogSeverity) sev));
        endInsertRows();
    }

    int EtherLog::getLogLevel() const {
        return fLogLevel;
    }

    void EtherLog::setLogLevel(int ll) {
        fLogLevel = (LogSeverity)ll;
        QSettings settings;
        settings.setValue("program/loglevel", ll);
    }

}
