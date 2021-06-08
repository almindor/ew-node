#include <QString>
#include <QtTest>
#include "helpers.h"

using namespace Etherwall;

class HelpersTest : public QObject
{
    Q_OBJECT

public:
    HelpersTest();

private Q_SLOTS:
    void hexPrefixTest();
    void clearHexPrefixTest();
    void toDecStrTest();
    void toDecStrEtherTest();
    void toHexStrTest();
    void toHexWeiStrTest();
    void decStrToHexStrTest();
    void weiStrToEtherStrTest();
    void baseStrToFullStrTest();
    void fullStrToBaseStrTest();
    void decStrToRossiTest();
    void etherStrToRossiTest();
    void formatEtherStrTest();
    void toQJsonArrayTest();
    void mergeJsonArraysTest();
    void toQUInt64Test();
    void parseAppVersionTest();
    void vitalizeAddressTest();
    void networkPostfixTest();
    void keccak256Test();
    void restoreBackupTest();
};

HelpersTest::HelpersTest()
{
}

void HelpersTest::hexPrefixTest()
{
    QCOMPARE(Helpers::hexPrefix("0"), QString("0x0"));
    QCOMPARE(Helpers::hexPrefix("47234"), QString("0x47234"));
    QCOMPARE(Helpers::hexPrefix("0x0"), QString("0x0"));
    QCOMPARE(Helpers::hexPrefix("0xffF"), QString("0xffF"));
    QCOMPARE(Helpers::hexPrefix("xx"), QString("0xxx"));
}

void HelpersTest::clearHexPrefixTest()
{
    QVERIFY(Helpers::clearHexPrefix("0x123") == QString("123"));
    QVERIFY(Helpers::clearHexPrefix("1x123") == QString("1x123"));
    QVERIFY(Helpers::clearHexPrefix("123") == QString("123"));
    QVERIFY(Helpers::clearHexPrefix("0xx123") == QString("x123"));
}

void HelpersTest::toDecStrTest()
{
    quint64 numVal = 234834642;
    const QJsonValue jsonVal("0xfefefefefefefefefefefefefefefe");
    QCOMPARE(Helpers::toDecStr(numVal), QString("234834642"));
    QCOMPARE(Helpers::toDecStr(jsonVal), QString("1324015336977916202813988209063558910"));
}

void HelpersTest::toDecStrEtherTest()
{
    const QJsonValue jsonVal("0xfefefefefefefefefefefefefefefe");
    QCOMPARE(Helpers::toDecStrEther(jsonVal), QString("1324015336977916202.813988209063558910"));
}

void HelpersTest::toHexStrTest()
{
    QCOMPARE(Helpers::toHexStr(235634674), QString("0xe0b7ff2"));
    QCOMPARE(Helpers::toHexStr(0), QString("0x0"));
}

void HelpersTest::toHexWeiStrTest()
{
    QCOMPARE(Helpers::toHexWeiStr("1"), QString("0xde0b6b3a7640000"));
    QCOMPARE(Helpers::toHexWeiStr("0.000000000000000001"), QString("0x1"));
}

void HelpersTest::decStrToHexStrTest()
{
    QCOMPARE(Helpers::decStrToHexStr("1"), QString("0x1"));
    QCOMPARE(Helpers::decStrToHexStr("1584"), QString("0x630"));
}

void HelpersTest::weiStrToEtherStrTest()
{
    QCOMPARE(Helpers::weiStrToEtherStr("1584"), QString("0.000000000000001584"));
    QCOMPARE(Helpers::weiStrToEtherStr("1000000000000000000"), QString("1.000000000000000000"));
}

void HelpersTest::baseStrToFullStrTest()
{
    QCOMPARE(Helpers::baseStrToFullStr("1", 18), QString("0.000000000000000001"));
    QCOMPARE(Helpers::baseStrToFullStr("1234", 3), QString("1.234"));
}

void HelpersTest::fullStrToBaseStrTest()
{
    QCOMPARE(Helpers::fullStrToBaseStr("0.000000000000000001", 18), QString("1"));
    QCOMPARE(Helpers::fullStrToBaseStr("1.234", 3), QString("1234"));
}

void HelpersTest::decStrToRossiTest()
{
    QCOMPARE(Helpers::decStrToRossi("1234"), BigInt::Rossi("1234", 10));
}

void HelpersTest::etherStrToRossiTest()
{
    QCOMPARE(Helpers::etherStrToRossi("1.234"), BigInt::Rossi("1234000000000000000", 10));
}

void HelpersTest::formatEtherStrTest()
{
    QCOMPARE(Helpers::formatEtherStr("1234567890.12345678"), QString("1234567890.123456780000000000"));
}

void HelpersTest::toQJsonArrayTest()
{
    AccountList list;
    list.append(AccountInfo("0x01", "test1", "ff1", "1.2345", 1, QString(), 3));
    list.append(AccountInfo("0x02", "test2", "ff2", "1.2347", 2, QString(), 3));
    list.append(AccountInfo("0x03", "test3", "ff3", "1.2346", 3, QString(), 3));
    list.append(AccountInfo("0x04", "test4", "ff4", "1.2343", 4, QString(), 3));
    list.append(AccountInfo("0x05", "test5", "ff5", "1.2342", 5, QString(), 3));

    const QJsonArray result = Helpers::toQJsonArray(list);
    QCOMPARE(result.size(), 5);
    QCOMPARE(result.at(0).toString(), QString("0x01"));
    QCOMPARE(result.at(1).toString(), QString("0x02"));
    QCOMPARE(result.at(2).toString(), QString("0x03"));
    QCOMPARE(result.at(3).toString(), QString("0x04"));
    QCOMPARE(result.at(4).toString(), QString("0x05"));
}

void HelpersTest::mergeJsonArraysTest()
{
    QJsonArray source;
    QJsonArray dest;

    QJsonArray sourceInner;
    sourceInner.append("si1");
    sourceInner.append("si2");

    source.append(QJsonValue("s0"));
    source.append(QJsonValue("s1"));
    source.append(QJsonValue(sourceInner));
    source.append(QJsonValue("s3"));

    QJsonArray destInner;
    destInner.append("di1");
    destInner.append("di2");

    dest.append(QJsonValue()); // null
    dest.append(QJsonValue("d1"));
    dest.append(QJsonValue(destInner));

    Helpers::mergeJsonArrays(dest, source);

    QCOMPARE(dest.size(), 4);
    QCOMPARE(dest.at(0).toString(), QString("s0"));
    QCOMPARE(dest.at(1).toArray().size(), 2);
    QCOMPARE(dest.at(1).toArray().at(0).toString(), QString("d1"));
    QCOMPARE(dest.at(1).toArray().at(1).toString(), QString("s1"));
    QCOMPARE(dest.at(2).toArray().size(), 4);
    QCOMPARE(dest.at(2).toArray().at(0).toString(), QString("di1"));
    QCOMPARE(dest.at(2).toArray().at(1).toString(), QString("di2"));
    QCOMPARE(dest.at(2).toArray().at(2).toString(), QString("si1"));
    QCOMPARE(dest.at(2).toArray().at(3).toString(), QString("si2"));
    QCOMPARE(dest.at(3).toString(), QString("s3"));
}

void HelpersTest::toQUInt64Test()
{
    QCOMPARE(Helpers::toQUInt64(QJsonValue("0xff")), (quint64) 255);
}

void HelpersTest::parseAppVersionTest()
{
    QCOMPARE(Helpers::parseVersion("1.2.3"), 102003);
}

void HelpersTest::vitalizeAddressTest()
{
    QCOMPARE(Helpers::vitalizeAddress("0x52bc44d5378309ee2abf1539bf71de1b7d7be3b5"), QString("0x52bc44d5378309EE2abF1539BF71dE1b7d7bE3b5"));
    QCOMPARE(Helpers::vitalizeAddress("0xa1c349e6fbe7579bd197ec380a3cd4fc89447dab"), QString("0xA1c349E6fBe7579bD197EC380a3Cd4FC89447dAB"));
    QCOMPARE(Helpers::vitalizeAddress("0xA1c349E6fBe7579bD197EC380a3Cd4FC89447dAB"), QString("0xA1c349E6fBe7579bD197EC380a3Cd4FC89447dAB"));
}

void HelpersTest::networkPostfixTest()
{
    QCOMPARE(Helpers::networkPostfix(0), QString("/unknown/unknown"));
    QCOMPARE(Helpers::networkPostfix(1), QString("/eth/homestead"));
    QCOMPARE(Helpers::networkPostfix(3), QString("/eth/ropsten"));
    QCOMPARE(Helpers::networkPostfix(4), QString("/eth/rinkeby"));
}

void HelpersTest::keccak256Test()
{
    QCOMPARE(Helpers::keccak256("a"), QByteArray::fromHex("3ac225168df54212a25c1c01fd35bebfea408fdac2e31ddd6f80a4bbf9a5f1cb"));
    QCOMPARE(Helpers::keccak256("idiomatic unit test"), QByteArray::fromHex("11d7ca97713076b607b1c1c1d91a8d76dca5401cc60fa3f530777b87ea02e9a5"));
}

void HelpersTest::restoreBackupTest()
{
    try {
        Helpers::restoreBackup(QByteArray(), QDir("/tmp"));
        QFAIL("should fail on empty backup");
    } catch ( QString err ) {
        QCOMPARE(err, QString("Invalid backup data"));
    }

    try {
        QByteArray raw;
        raw.append(255, 8); // size, crc and 2bytes invalid data
        Helpers::restoreBackup(qCompress(raw, 9), QDir("/tmp"));
        QFAIL("should fail on bad CRC");
    } catch ( QString err ) {
        QCOMPARE(err, QString("CRC check mismatch: 2056 != 0"));
    }
}

QTEST_APPLESS_MAIN(HelpersTest)

#include "tst_helperstest.moc"
