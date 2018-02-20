/*
    This file is part of etherwall.
    etherwall is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    etherwall is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with etherwall. If not, see <http://www.gnu.org/licenses/>.
*/
/** @file etheripc.h
 * @author Ales Katona <almindor@gmail.com>
 * @date 2015
 *
 * Ethereum IPC client header
 */

#ifndef ETHERIPC_H
#define ETHERIPC_H

#include <QObject>
#include <QQueue>
#include <QLocalSocket>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>
#include <QTimer>
#include <QThread>
#include <QProcess>
#include <QTime>
#include <QVariantMap>
#include "types.h"
#include "etherlog.h"
#include "gethlog.h"
#include "ethereum/bigint.h"
#include "ethereum/tx.h"

namespace Etherwall {

    enum NodeRequestBurden {
        Full,
        NonVisual,
        None
    };

    class NodeRequest {
    public:
        NodeRequest(NodeRequestBurden burden, NodeRequestTypes type, const QString method, const QJsonArray params = QJsonArray(), int index = -1);
        NodeRequest(NodeRequestTypes type, const QString method, const QJsonArray params = QJsonArray(), int index = -1);
        NodeRequest(NodeRequestBurden burden);

        NodeRequestTypes getType() const;
        const QString& getMethod() const;
        const QJsonArray& getParams() const;
        int getIndex() const;
        const QVariantMap getUserData() const;
        void setUserData(const QVariantMap& data);
        int getCallID() const;
        NodeRequestBurden burden() const;
        static int sCallID;
    private:
        int fCallID;
        NodeRequestTypes fType;
        QString fMethod;
        QJsonArray fParams;
        int fIndex;
        QVariantMap fUserData;
        NodeRequestBurden fBurden;
    };

    typedef QQueue<NodeRequest> RequestQueue;

    class NodeIPC: public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString error READ getError NOTIFY error)
        Q_PROPERTY(int code READ getCode NOTIFY error)
        Q_PROPERTY(bool external READ getExternal NOTIFY externalChanged)
        Q_PROPERTY(bool busy READ getBusy NOTIFY busyChanged)
        Q_PROPERTY(bool starting READ getStarting NOTIFY startingChanged)
        Q_PROPERTY(bool syncing READ getSyncingVal NOTIFY syncingChanged)
        Q_PROPERTY(bool closing READ getClosing NOTIFY closingChanged)
        Q_PROPERTY(int connectionState READ getConnectionState NOTIFY connectionStateChanged)
        Q_PROPERTY(quint64 peerCount READ peerCount NOTIFY peerCountChanged)
        Q_PROPERTY(QString clientVersion MEMBER fClientVersion NOTIFY clientVersionChanged)
        Q_PROPERTY(int netVersion MEMBER fNetVersion NOTIFY netVersionChanged)
        Q_PROPERTY(bool testnet READ getTestnet NOTIFY netVersionChanged)
        Q_PROPERTY(quint64 currentBlock READ getCurrentBlock NOTIFY syncingChanged)
        Q_PROPERTY(quint64 highestBlock READ getHighestBlock NOTIFY syncingChanged)
        Q_PROPERTY(quint64 startingBlock READ getStartingBlock NOTIFY syncingChanged)
        Q_PROPERTY(quint64 blockNumber MEMBER fBlockNumber NOTIFY getBlockNumberDone)
        Q_PROPERTY(QString activeRequestName READ getActiveRequestName NOTIFY requestChanged)
    public:
        NodeIPC(GethLog& gethLog);
        virtual ~NodeIPC();
        void init();
        virtual bool isThinClient() const;

        void setWorker(QThread* worker);
        bool getBusy() const;
        bool getExternal() const;
        bool getStarting() const;
        bool getClosing() const;
        const QString& getError() const;
        int getCode() const;
        bool getTestnet() const;
        const QString getNetworkPostfix() const;
        quint64 blockNumber() const;
        int network() const;
        quint64 nonceStart() const;
        void getAccounts();
        bool refreshAccount(const QString& hash, int index);
        void newAccount(const QString& password, int index);
        void getBlockNumber();
        void loadLogs(const QStringList& addresses, const QJsonArray& topics, quint64 fromBlock, const QString& internalID);
        void getGasPrice();
        void sendTransaction(const Ethereum::Tx& tx, const QString& password);
        void signTransaction(const Ethereum::Tx& tx, const QString& password);
        void signTransaction(const Ethereum::Tx& tx);
        void sendRawTransaction(const Ethereum::Tx& tx);
        void sendRawTransaction(const QString &rlp);
        void call(const Ethereum::Tx& tx, int index, const QVariantMap& userData);
        void getTransactionByHash(const QString& hash);
        void newEventFilter(const QJsonArray& addresses, const QJsonArray& topics, const QString& internalID);
        void uninstallFilter(const QString& internalID);
        void registerIpcErrorHandler(int code, IPCReplyErrorHandler handler);

        Q_INVOKABLE virtual bool closeApp();
        Q_INVOKABLE virtual void setInterval(int interval);
        Q_INVOKABLE void estimateGas(const QString& from, const QString& to, const QString& valStr,
                                     const QString& gas, const QString& gasPrice, const QString& data);
        Q_INVOKABLE void getTransactionReceipt(const QString& hash);

        // static & global
        static const QString defaultIPCPath(const QString& dataDir, bool testnet);

        static const QString sDefaultDataDir;
        static const QString sDefaultGethArgs;
    public slots:
        virtual void start(const QString& progStr, const QString& version, const QString& endpoint, const QString& warning);
    protected slots:
        void waitConnect();
        void connectToServer();
        void connectedToServer();
        void connectionTimeout();
        void disconnectedFromServer();
        void onSocketReadyRead();
        void onSocketError(QLocalSocket::LocalSocketError err);
        void onIpcReady();
        void onRequestDone();
        void onStopTimer();
    signals:
        void connectToServerDone();
        void getAccountsDone(const QStringList& list) const;
        void newAccountDone(const QString& result, int index) const;
        void unlockAccountDone(bool unlocked, int index) const;
        void getBlockNumberDone(quint64 num) const;
        void sendTransactionDone(const QString& hash) const;
        void signTransactionDone(const QString& hash) const;
        void callDone(const QString& result, int index, const QVariantMap& userData) const;
        void getGasPriceDone(const QString& price) const;
        void estimateGasDone(const QString& price) const;
        void newTransaction(const QJsonObject& info) const;
        void newBlock(const QJsonObject& block) const;
        void newEvent(const QJsonObject& event, bool isNew, const QString& filterID) const;
        void getTransactionReceiptDone(const QJsonObject& receipt) const;

        void peerCountChanged(quint64 num) const;
        void accountBalanceChanged(int index, const QString& balanceStr) const;
        void accountSentTransChanged(int index, quint64 count) const;
        void busyChanged(bool busy) const;
        void requestChanged() const;
        void externalChanged(bool external) const;
        void startingChanged(bool starting) const;
        void syncingChanged(bool syncing) const;
        void closingChanged(bool closing) const;
        void connectionStateChanged() const;
        void clientVersionChanged(const QString& ver) const;
        void netVersionChanged(int ver) const;
        void error() const;
        void ipcReady() const;
        void requestDone() const;
        void stopTimer() const;
    protected:
        QString fPath;
        QLocalSocket fSocket;
        QString fBlockFilterID;
        bool fClosingApp;
        quint64 fPeerCount;
        QString fReadBuffer;
        QString fError;
        int fCode;
        TransactionList fTransactionList;
        RequestQueue fRequestQueue;
        NodeRequest fActiveRequest;
        QTimer fTimer;
        int fNetVersion;
        QString fClientVersion;
        QProcess fGeth;
        int fStarting;
        GethLog& fGethLog;
        bool fSyncing;
        quint64 fCurrentBlock;
        quint64 fHighestBlock;
        quint64 fStartingBlock;
        int fConnectAttempts;
        QTime fKillTime;
        bool fExternal;
        QMap<QString, QString> fEventFilterIDs;
        quint64 fBlockNumber;
        QString fReceivedMsg;
        QString fProgStr;
        IPCReplyErrorHandlerList fIPCReplyErrorHandlerList;

        void handleNewAccount();
        void handleGetAccounts();
        void handleAccountBalance();
        void handleAccountTransactionCount();
        void handleGetBlockNumber();
        void handleGetPeerCount();
        void handleSendTransaction();
        void handleSignTransaction();
        void handleCall();
        void handleGetGasPrice();
        void handleEstimateGas();
        void handleNewBlockFilter();
        void handleNewEventFilter();
        void handleGetFilterChanges();
        void handleUninstallFilter();
        void handleGetTransactionByHash();
        void handleGetBlock();
        void handleGetTransactionReceipt();
        void handleGetClientVersion();
        void handleGetNetVersion();
        void handleGetSyncing();
        void handleUnlockAccount();

        // virtual
        virtual void finishInit();
        virtual bool endpointWritable();
        virtual qint64 endpointWrite(const QByteArray& data);
        virtual const QByteArray endpointRead();
        virtual const QStringList buildGethArgs();

        void onTimer();
        bool killGeth();
        int parseVersionNum() const;
        void unlockAccount(const QString& hash, const QString& password, int duration, int index);
        bool getBalance(const QString& hash, int index);
        bool getTransactionCount(const QString& hash, int index);
        void getSyncing();
        void getFilterChanges(const QString& filterID, const QString& internalFilterID);
        void getClientVersion();
        void getNetVersion();
        void getPeerCount();
        bool getSyncingVal() const;
        void getBlockByHash(const QString& hash);
        void getBlockByNumber(quint64 blockNum);
        quint64 getCurrentBlock() const;
        quint64 getHighestBlock() const;
        quint64 getStartingBlock() const;
        int getConnectionState() const;
        quint64 peerCount() const;
        void bail(bool soft = false);
        void setError(const QString& error);
        void errorOut();
        void done();
        void newBlockFilter();
        virtual void getLogs(const QStringList& addresses, const QJsonArray& topics, quint64 fromBlock, const QString& internalID);

        QJsonObject methodToJSON(const NodeRequest& request);
        bool queueRequest(const NodeRequest& request);
        bool writeRequest(const NodeRequest& request);
        bool readData();
        bool readReply(QJsonValue& result);
        bool readVin(BigInt::Vin& result);
        bool readNumber(quint64& result);
        const QString getActiveRequestName() const;
        const QString toDecStr(const QJsonValue& jv) const;
        void handleRequest();
    };

}

#endif // ETHERIPC_H

