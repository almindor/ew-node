#include "networkchainmanager.h"

namespace Etherwall {

    NetworkChainManager::NetworkChainManager() :
        fChainID(-1), fChainName(), fNetworkPostfix(), fTestnet(false), fHDPathBase()
    {
    }

    int NetworkChainManager::chainID() const
    {
        return fChainID;
    }

    const QString NetworkChainManager::chainName() const
    {
        return fChainName;
    }

    const QString NetworkChainManager::networkPostfix() const
    {
        return fNetworkPostfix;
    }

    bool NetworkChainManager::testnet() const
    {
        return fTestnet;
    }

    const QString NetworkChainManager::hdPathBase() const
    {
        return fHDPathBase;
    }

    void NetworkChainManager::init(int chainID)
    {
        fChainID = chainID;
        switch ( chainID ) {
            case 1: setHomestead(); break;
            case 3: setRopsten(); break;
            case 4: setRinkeby(); break;
            case 42: setKovan(); break;
            default: throw QString("Unknown chainID");
        }
        fHDPathBase = getHDPathBase(); // only 2 variants, mainnet or testnet
    }

    const QString NetworkChainManager::getHDPathBase() const
    {
        if ( fTestnet ) {
            // test net: m/44'/1'/0'/0/<index>
            return "m/44'/1'/0'/0";
        }

        // main net: m/44'/60'/0'/0/<index>
        return "m/44'/60'/0'/0";
    }

    void NetworkChainManager::setHomestead()
    {
        fChainName = "homestead";
        fNetworkPostfix = "/eth/homestead";
        fTestnet = false;
    }

    void NetworkChainManager::setRopsten()
    {
        fChainName = "homestead";
        fNetworkPostfix = "/eth/ropsten";
        fTestnet = true;
    }

    void NetworkChainManager::setRinkeby()
    {
        fChainName = "rinkeby";
        fNetworkPostfix = "/eth/rinkeby";
        fTestnet = true;
    }

    void NetworkChainManager::setKovan()
    {
        fChainName = "kovan";
        fNetworkPostfix = "/eth/kovan";
        fTestnet = true;
    }

}
