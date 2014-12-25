// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

//
// Main network
//

unsigned int pnSeed[] =
{
        0x3db2528b, 0xa0cfa5bc, 0x609ec836, 0x90e9156b, 0xd9baa76b, 0x9ad19f55, 0x677c98c8, 0x5bc3f6da,
        0x829a3eb2, 0x886f8a43, 0x7c1afc2e, 0x72218368, 0x97d59dc0, 0x66b2528b, 0xf216ba6a, 0x29b9b992,
        0xf77ddf4e, 0x4530dc1f, 0x0e431c45, 0x55efaa6b, 0x95d9aa6b, 0xb075c7c6, 0x3b1eba6a, 0x99e04cad,
        0xab745c57, 0xed174142, 0xdda23eb2, 0x468bfeb6, 0x5b24aa58, 0x80a03eb2, 0x823300ad, 0xc9ec2fd4,
        0x540dc405, 0xaca34305, 0x522ad176, 0x5713a4d8, 0x0f58e9bc, 0x5ae0574f, 0x9d743ac6, 0x7c561dde,
        0x8c5cc818, 0xcd5cd454, 0x75af3851, 0xce0e255c, 0xad0be9bc, 0x956d7e2e, 0x6a902002, 0x28d4482e,
        0xfc22a068, 0x0c862442, 0x84a67870, 0x45dae64e, 0x37bd1dd9, 0x4122555f, 0x5ab6b95d, 0xaec8cc47,
        0xa08ad54e, 0x165df950, 0xdf19ca5b, 0xb8324ada, 0xeb6d3ac6, 0xd85ce362, 0x89ffba32, 0x48c5e052,
        0xb2ecd048, 0xe580e068, 0x48261a3d, 0x3f5e9c5a, 0xe68ba1cb, 0xe40ec273, 0x87dd6f4f, 0x270a5975,
        0xf3035272, 0xef802442, 0x8068777d, 0xa3a8dacb, 0x71e9ae6e, 0x30cdc973, 0x778ad54e, 0x8e50e08c,
        0x44bb48de, 0x8bc6bb25, 0x48515d72, 0x344dfd54, 0xc22ad0a2, 0x41671bb2, 0xf2cd3c92, 0x50161a3d,
        0xc49e206e, 0x5dc27161, 0xc5aba33e, 0x56e96db6, 0x543eddd8, 0x65c3eb7a, 0x74456077, 0xca56c082,
        0x0a818b77, 0x8885cc25, 0x6753fd72, 0xfb61fc6d, 0xb4af7a7d, 0x06fbd05e, 0x55b39a0e, 0x3ac9482e,
        0x7894f472, 0x36e60401, 0x6b5e787d, 0x743ddd72, 0xf022c2bc, 0x2f37be6d, 0xd1bfb87c, 0x4289206e,
        0x8c4da976, 0xdcc41dc9, 0x8deb0401, 0x72e50401, 0x5d27bbbc, 0x4e46c281, 0x8a9f2442, 0x59e39f2a,
        0xfba0221f, 0x3e154171, 0xcadf5e02, 0x6d25105a, 0x8570bd12, 0x7c0ae6bc, 0x132dbe6d, 0x1212b37c,
        0x194b5d72, 0xe7aa0e79, 0xcb24f874, 0x03fe0401, 0xa3cf3c92, 0xc1e80401, 0xbcc0206e, 0x7eba16c9,
        0xeec4ba56, 0x721cbd54, 0x33af7631, 0x1ca8e95e, 0x61c31f5d, 0x4eb2528b, 0xab2dbd54, 0x30154605,
        0xc02fa43a, 0x37b5a056, 0xe5317059, 0x608b20bc, 0xb5a6505d, 0x8c6b2549, 0x3cf32b43, 0xd2465d72,
        0x9a387059, 0xe3be1dc9, 0xa036546a, 0x9afbe44f, 0xdcd25872, 0x86ca206e, 0xd931439a, 0x69f60401,
        0x9c595d72, 0x7e764658, 0x45c8e179, 0xc910a201, 0xd4bdea4e, 0x9b69695c, 0xa79ab07c, 0x5993d46d,
        0xfa3a7059, 0xc5d6d5ba, 0x4c51e08c, 0xaf2c61b1, 0x5e7eecb3, 0xb9419cba, 0xe7fa9d6d, 0x6846c36e,
        0x34d3846d, 0x49a2301f, 0x55bd5252, 0x75a2767d, 0xb8a208af, 0x59c6206e, 0x34314e5c, 0xbfe60c1b,
        0xf688b455, 0xad528fb4, 0xf795df5e, 0x53a3135d, 0xe72abd54, 0xd7485393, 0x5f22ec59, 0xe89dfc71,
        0x35f0e44f, 0x0a90b455, 0x989ab54f, 0x27ababb4, 0xab682cbc, 0x236b828a, 0x706b5d02, 0x6237787b,
        0x890bf572, 0x4c4ba4dc, 0xdf500c87, 0x3929b2cd, 0x296a6d2e, 0x9d9f80db, 0x10fad5ba, 0xfee0533e,
        0x851504c9, 0x9dc17470, 0xf9d2126e, 0x4a6f3fb7, 0x676d4471, 0x2b184e5c, 0x9d893251, 0xe6a9254e,
        0x6d297059, 0x63d667d5, 0xef09517a, 0xa500bd54, 0x0b43c36e, 0x5fa88156, 0x2f45c36e, 0x93de5658,
        0x2b2a173a, 0x6d6d4471, 0x898aa53d, 0xe03efb76, 0x83c15a4b, 0xbbcb482e, 0x92d2d5ba, 0x27810477,
        0x14f50401, 0xbea40244, 0x8c7ff12e, 0x7626bb58, 0xccf86c4e, 0xbc86b455, 0xf3e7ba58, 0x29845d02,
        0x02e10bc6, 0xe569e352, 0x3b8d6944, 0xc5740a1b, 0x7c40de4e, 0x1ef9d5ba, 0xacb7f5dc, 0xef2d0f1b,
        0x48e58b50, 0x3ae00401, 0xf7ab3244, 0xe38cb455, 0x631ff671, 0x569a515d, 0x4ef51f5f, 0x3038c26e,
        0xbda2a165, 0xc51c4150, 0x5470a243, 0xd14af976, 0x9520f4bc, 0x4a5434c9, 0x3144c170, 0xa628904e,
        0x9676e36d, 0xaf3b7059, 0x1b28b458, 0x3052690e, 0xa6afc6dd, 0x67c85dab, 0x5e1408b2, 0xfc15b2d4,
        0x1054972e, 0xe5ea0401, 0x0596206e, 0xa1031bbd, 0x9c2bcc62, 0x5d50e08c, 0x97d7cd9f, 0xd09df3a2,
        0xaef5055a, 0x9050e08c, 0xe07d4605, 0xceabf1ba, 0xdd63256a, 0x15bf454b, 0x84285272, 0x31892002,
        0x91bab3de, 0xd67cf972, 0x0ce81dc9, 0xbf6f41ad, 0xc6d90db7, 0x24a2f2b6, 0x52f1a07c, 0xe7e0ed82,
        0x4baf728d, 0xc9cdd5ba, 0x183b6272, 0x901ef2b6, 0x8bf6cd2e, 0x36f5c36e, 0x1d5f6f4f, 0x4f9f5231,
        0xacd9d5ba, 0x62533e46, 0x74378725, 0x8180ac77, 0x4840733b, 0xa7a130ba, 0x00d3f572, 0x6ef79c3e,
        0x57071979, 0x094a225b, 0xf492787d, 0x26aa10b7, 0x0b69cdb1, 0x4968cdb1, 0xd182cf1f, 0x4197b455,
        0x177daade, 0xee4d9f1b, 0x1ac122b2, 0xd82b2c5c, 0x79505d72, 0xa38ab455, 0xbe2b9e7b, 0x399afc71,
        0xe39dd6ba, 0xbf9af1ba, 0xfc455d72, 0xc538d879, 0x6e8ea065, 0x02e2ff3a, 0x7d154171, 0xfb529389,
        0xbc4ac36e, 0x47811855, 0xcd0ab86e, 0x50dc164d, 0xac70cb7b, 0xb8dad73c, 0x87f0c36e, 0xc3ded5ba,
        0x9f55372e, 0x181819ad, 0xb7d5482e, 0x580a737b, 0xfd9bcd3e, 0x70a648de, 0x4e431979, 0x3a465d72,
        0xeb50e08c, 0x264d4e7c, 0xd28db455, 0x21500c87, 0x10bcae3b, 0xd2bcae65, 0xe2e9a377, 0xec54fe18,
        0xcf26d05a, 0x7399d6ba, 0xbb9b2eb7, 0x88480852, 0x33e89389, 0x16c01b3c, 0x1b789aa5, 0x4f903a4d,
        0x96ea9f7b, 0x75dbfc3c, 0xbfb0a658, 0x6d8366b4, 0x74fee874, 0x4af6cd2e, 0x3f76690e, 0x43c0002e,
        0x5a516270, 0xbf82cb1b, 0x8ad255df, 0x5333d91b, 0x57b8b858, 0x7474507a, 0x4c04a63a, 0xe6add6ba,
        0x120e1874, 0x4141c86e, 0xe3a4f872, 0xf399e179, 0xcf2b41de, 0xbb5d25b7, 0xb2c57cb2, 0xe48bc22e,
        0x54f34250, 0x7efb1974, 0x8850e08c, 0x6082eadd, 0x2f1a1bbd, 0xf0ed6b54, 0x9240507a, 0x47b7a63d,
        0x199fc257, 0x38266b51, 0x60f0b47c, 0xe948217d, 0x4d500c87, 0xd2d8b47c, 0xf0f6bb3d, 0xb28f8368,
        0x431aa0b4, 0x5d5be974, 0xd2e90a1b, 0xb6756377, 0x9007f470, 0xe2f3ae55, 0xbfa4227d, 0x555ab259,
        0x98d5384a, 0x9bb04371, 0x03e2ff3a, 0x8d940db7, 0x06ce51bd, 0x71797080, 0xec4cec5c, 0x33e8d979,
        0x80883924, 0x72811056, 0x1e85b455, 0x0b86be6b, 0x92f2cd2e, 0xb9b8f371, 0xe8ced6ab, 0x7da4c88b,
        0x9562fbb0, 0x9803be6d, 0x2db51cc2, 0x662b2177, 0x9d9dfc71, 0xc0a31118, 0x1544c170, 0x48b8096b,
        0x54350e70, 0x7e282177, 0x9e139473, 0x429b0344, 0x8c8232ba, 0x376d4071, 0x0f0d1979, 0x329dfc71,
        0x7e586171, 0x8e6c7276, 0xe84d5f70, 0x5c38e670, 0xfd8d2d70, 0x706b60b8, 0x839a1853, 0x775a5975,
        0x3e8fb455, 0x4a585378, 0x5151375f, 0x65c5c39e, 0xef8eb67b, 0x30e36871, 0x7d80811f, 0x4cda0eb0,
        0x387e692e, 0x6a53787b, 0xf4b0a56f, 0x5312a932, 0xa720f5dc, 0xfcad9389, 0xbd500c87, 0x6a48b756,
        0x53644465, 0x982c1bbd, 0xdff947b2, 0x860322b7, 0xbc84b455, 0x5295d2b2, 0x46fea6dc, 0xff1c1979,
        0x820b5975, 0x0a97b455, 0xa61058df, 0x841db05b, 0xe7be750e, 0xd58c4305, 0xc634dd72, 0xd2fcae55,
        0x0e1be9db, 0x442a7b7b, 0xd1e31dc9, 0xea64e32a, 0x1708e9dc, 0x624479c0, 0x89d49e7c, 0xeee00b79,
        0x88a9be6d, 0x52855718, 0xb8d1dd72, 0x88524252, 0x154c652a, 0x6f88253a, 0x76225a75, 0x6e8d357b,
        0x375f0653, 0x7d50cd1b, 0xcd892218, 0x8c1f4f59, 0x1bb9303d, 0xf1d1497d, 0xa08c11b7, 0x980f27b7,
        0x7129321f, 0xa7ed84b1, 0xad93b8dc, 0x7d50e08c, 0xc73bd9de, 0x7c566c59, 0x3156957b, 0x9d899dd9,
        0x3705b47c, 0x935b6270, 0xd68d81b6, 0xebfc727b, 0xf5f55301, 0x04292177, 0x2d81a7df, 0x70b7c27a,
        0xd0a11c75, 0xf62b173a, 0x268d81b6, 0x74ced6ab, 0x78add61b, 0x29987e0e, 0xcaad16d2, 0x77ae8e5b,
        0xc94fc268, 0x8d92cd18, 0x2bced6ab, 0xc78ae75a, 0xccb02843, 0xf292506a, 0x26995353, 0x37af7871,
        0x6a22a068, 0xc665063c, 0x0cc0fc1b, 0xe2aa0e79, 0xf7c1c147, 0xa7a0b032, 0x0a6d58b6, 0xbc4bf771,
        0xcb5a9bc0, 0xac9cfc71, 0x2e50e08c, 0x90bd3077, 0xfccb5171, 0x67edf7b7, 0x54e03fda, 0x56fa5971,
        0x93aed61b, 0xc5baa77c, 0x70f64675, 0x5c925675, 0xd4861e53, 0x463e2db7, 0xc881da73, 0x4b72170e,
        0x1589b455, 0xde3d21b6, 0x1fa2a956, 0x9634b975, 0x84ecb8b7, 0xda834fdf, 0xe0712b7d, 0x8ccccb45,
        0xd3d95ede, 0x193a524f, 0x274b7274, 0xa1e89bb4, 0x7997b455, 0xa31df57b, 0xe6a4598f, 0x449f1787,
        0xd7da0db7, 0xa4a1dd57, 0x32b0a1b4, 0x5300bb25, 0xcd50e08c, 0x8a9331c3, 0x350d1801, 0x621f173a,
        0xc08d1874, 0x2727787b, 0xc2733156, 0x3097357b, 0xb835787b, 0xc6a3bfde, 0x1ad3884f, 0xef822442
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xf0;
        pchMessageStart[1] = 0xda;
        pchMessageStart[2] = 0xbb;
        pchMessageStart[3] = 0xd2;
        vAlertPubKey = ParseHex("04fc9702847840aaf195de8442ebecedf5b095cdbb9bc716bda9110971b28a49e0ead8564ff0db22209e0374782c093bb899692d524e9d6a6956e7c5ecbcd68284");
        nDefaultPort = 28333;
        nRPCPort = 28332;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        nTxBits = 0x1e00ffff;
        nSubsidyHalvingInterval = 210000;

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        // CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
        //   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
        //     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
        //   vMerkleTree: 4a5e1e
        const char* pszTimestamp = "The Times 09/Jul/2013 Globo caught bribing Receita Federal employee to rob R$615M worth tax evasion documents.";
        CTransaction txNew;
        txNew.message = CScript() << string(pszTimestamp);
        txNew.userName = CScript() << string("nobody");
        txNew.nNonce  = 0; // spamMessage is not required to show POW to ease "extranonce" support
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nHeight  = 0;
        genesis.nTime    = 1384394255;
        //genesis.nBits    = 0x1d00ffff;
        genesis.nBits    = 0x1f03ffff;
        genesis.nNonce   = 2934;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("9915158279673d101912be80f25c20627f1dd8bf5231e7c46bfec5ed19737f44"));

        vSeeds.push_back(CDNSSeedData("twister.net.co", "seed.twister.net.co"));
        vSeeds.push_back(CDNSSeedData("gombadi.com", "dnsseed.gombadi.com"));
        vSeeds.push_back(CDNSSeedData("twister.net.co", "seed2.twister.net.co"));
        vSeeds.push_back(CDNSSeedData("twister.net.co", "seed3.twister.net.co"));
        vSeeds.push_back(CDNSSeedData("twisterseed.tk", "twisterseed.tk"));
        vSeeds.push_back(CDNSSeedData("cruller.tasty.sexy", "cruller.tasty.sexy"));
        vSeeds.push_back(CDNSSeedData("twister-seeder.muh.freedu.ms", "twister-seeder.muh.freedu.ms"));

        base58Prefixes[PUBKEY_ADDRESS] = 0;
        base58Prefixes[SCRIPT_ADDRESS] = 5;
        base58Prefixes[SECRET_KEY] = 128;

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64 nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x0b;
        pchMessageStart[1] = 0x11;
        pchMessageStart[2] = 0x09;
        pchMessageStart[3] = 0x07;
        vAlertPubKey = ParseHex("04302390343f91cc401d56d68b123028bf52e5fca1939df127f63c6467cdf9c8e2c14b61104cf817d0b780da337893ecc4aaff1309e536162dabbdb45200ca2b0a");
        nDefaultPort = 18333;
        nRPCPort = 18332;
        strDataDir = "testnet3";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1296688602;
        genesis.nNonce = 414098458;
        hashGenesisBlock = genesis.GetHash();
        //assert(hashGenesisBlock == uint256("000000000933ea01ad0ee984209779baaec3ced90fa3f408719526f8d77f4943"));

        vFixedSeeds.clear();
        vSeeds.clear();
        //vSeeds.push_back(CDNSSeedData("bitcoin.petertodd.org", "testnet-seed.bitcoin.petertodd.org"));
        //vSeeds.push_back(CDNSSeedData("bluematt.me", "testnet-seed.bluematt.me"));

        base58Prefixes[PUBKEY_ADDRESS] = 111;
        base58Prefixes[SCRIPT_ADDRESS] = 196;
        base58Prefixes[SECRET_KEY] = 239;

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        nTxBits = 0x207fffff;
        genesis.nTime = 1296688602;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        //assert(hashGenesisBlock == uint256("0x0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.

        base58Prefixes[PUBKEY_ADDRESS] = 0;
        base58Prefixes[SCRIPT_ADDRESS] = 5;
        base58Prefixes[SECRET_KEY] = 128;
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
