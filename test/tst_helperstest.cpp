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

QTEST_APPLESS_MAIN(HelpersTest)

#include "tst_helperstest.moc"
