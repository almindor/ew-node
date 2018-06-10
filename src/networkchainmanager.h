#ifndef NETWORKCHAINMANAGER_H
#define NETWORKCHAINMANAGER_H

#include <QString>

namespace Etherwall {

    class NetworkChainManager
    {
    public:
        NetworkChainManager();
        int chainID() const;
        const QString chainName() const;
        const QString networkPostfix() const;
        bool testnet() const;
        const QString hdPathBase() const;
        void init(int chainID);
    private:
        int fChainID;
        QString fChainName;
        QString fNetworkPostfix;
        bool fTestnet;
        QString fHDPathBase;

        const QString getHDPathBase() const;
        void setHomestead();
        void setRopsten();
        void setRinkeby();
        void setKovan();
    };

}

#endif // NETWORKCHAINMANAGER_H
