# etherwall node implementation

ew-node is the base layer of Etherwall. ew-node implements IPC and WS nodes to communicate with geth along helper classes and tests.

## Donations

#### Flattr
[![Flattr this git repo](http://api.flattr.com/button/flattr-badge-large.png)](https://flattr.com/submit/auto?user_id=Almindor&url=https://github.com/almindor/etherwall&title=Etherwall&language=&tags=github&category=software)

#### Bitcoin
`1NcJoao879C1pSKvFqnUKD6wKtFpCMppP6`

#### Litecoin
`LcTfGmqpXCiG7UikBDTa4ZiJMS5cRxSXHm`

#### Ether
`0xC64B50dB57c0362e27A32b65Bd29363f29FDFa59`

## Development

### General Requirements

[Qt5.6+ with qmake](https://www.qt.io/developers/)

Qt5 modules:
* qt5-websockets

### Testing

```
qmake test.pro
make
./tst_helperstest
```

#### TODO

Add tests for RLP conversion methods
Add node tests
