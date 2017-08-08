#include "bmcl/Sha3.h"

#include "BmclTest.h"
#include "bmcl/Logging.h"
#include "bmcl/ArrayView.h"
#include "bmcl/FixedArrayView.h"
#include "bmcl/StringView.h"
#include "bmcl/Buffer.h"

#include <cstddef>
#include <cstdio>
#include <cstring>

using namespace bmcl;

// test vectors from
// http://csrc.nist.gov/groups/ST/toolkit/examples.html
// http://www.di-mgt.com.au/sha_testvectors.html

template <typename T>
class Sha3Test : public ::testing::Test {
protected:

};

struct Ctx224 {
    Sha3<224> ctx;
};

struct Ctx256 {
    Sha3<256> ctx;
};

struct Ctx384 {
    Sha3<384> ctx;
};

struct Ctx512 {
    Sha3<512> ctx;
};

static std::vector<uint8_t> dataA3(200, 0xa3);
static std::vector<uint8_t> data61(1000000, 0x61);

struct Data0 {
	std::vector<uint8_t> data;
};

struct Data1600 {
	std::vector<uint8_t> data = dataA3;
};

struct Data8000000 {
	std::vector<uint8_t> data = data61;
};

struct Sha3_224_0bit : Ctx224, Data0 {
    std::vector<uint8_t> hash = {{
        0x6b, 0x4e, 0x03, 0x42, 0x36, 0x67, 0xdb, 0xb7,
        0x3b, 0x6e, 0x15, 0x45, 0x4f, 0x0e, 0xb1, 0xab,
        0xd4, 0x59, 0x7f, 0x9a, 0x1b, 0x07, 0x8e, 0x3f,
        0x5b, 0x5a, 0x6b, 0xc7,
    }};
};

struct Sha3_224_1600bit : Ctx224, Data1600 {
	std::vector<uint8_t> hash = {{
        0x93, 0x76, 0x81, 0x6a, 0xba, 0x50, 0x3f, 0x72,
        0xf9, 0x6c, 0xe7, 0xeb, 0x65, 0xac, 0x09, 0x5d,
        0xee, 0xe3, 0xbe, 0x4b, 0xf9, 0xbb, 0xc2, 0xa1,
        0xcb, 0x7e, 0x11, 0xe0,
    }};
};

struct Sha3_224_8000000bit : Ctx224, Data8000000 {
	std::vector<uint8_t> hash = {{
        0xd6, 0x93, 0x35, 0xb9, 0x33, 0x25, 0x19, 0x2e,
        0x51, 0x6a, 0x91, 0x2e, 0x6d, 0x19, 0xa1, 0x5c,
        0xb5, 0x1c, 0x6e, 0xd5, 0xc1, 0x52, 0x43, 0xe7,
        0xa7, 0xfd, 0x65, 0x3c,
    }};
};

struct Sha3_256_0bit : Ctx256, Data0 {
public:
	std::vector<uint8_t> hash = {{
        0xa7, 0xff, 0xc6, 0xf8, 0xbf, 0x1e, 0xd7, 0x66,
        0x51, 0xc1, 0x47, 0x56, 0xa0, 0x61, 0xd6, 0x62,
        0xf5, 0x80, 0xff, 0x4d, 0xe4, 0x3b, 0x49, 0xfa,
        0x82, 0xd8, 0x0a, 0x4b, 0x80, 0xf8, 0x43, 0x4a
    }};
};

struct Sha3_256_1600bit : Ctx256, Data1600 {
	std::vector<uint8_t> hash = {{
        0x79, 0xf3, 0x8a, 0xde, 0xc5, 0xc2, 0x03, 0x07,
        0xa9, 0x8e, 0xf7, 0x6e, 0x83, 0x24, 0xaf, 0xbf,
        0xd4, 0x6c, 0xfd, 0x81, 0xb2, 0x2e, 0x39, 0x73,
        0xc6, 0x5f, 0xa1, 0xbd, 0x9d, 0xe3, 0x17, 0x87
    }};
};

struct Sha3_256_8000000bit : Ctx256, Data8000000 {
	std::vector<uint8_t> hash = {{
        0x5c, 0x88, 0x75, 0xae, 0x47, 0x4a, 0x36, 0x34,
        0xba, 0x4f, 0xd5, 0x5e, 0xc8, 0x5b, 0xff, 0xd6,
        0x61, 0xf3, 0x2a, 0xca, 0x75, 0xc6, 0xd6, 0x99,
        0xd0, 0xcd, 0xcb, 0x6c, 0x11, 0x58, 0x91, 0xc1,
    }};
};

struct Sha3_384_0bit : Ctx384, Data0 {
	std::vector<uint8_t> hash = {{
        0x0c, 0x63, 0xa7, 0x5b, 0x84, 0x5e, 0x4f, 0x7d,
        0x01, 0x10, 0x7d, 0x85, 0x2e, 0x4c, 0x24, 0x85,
        0xc5, 0x1a, 0x50, 0xaa, 0xaa, 0x94, 0xfc, 0x61,
        0x99, 0x5e, 0x71, 0xbb, 0xee, 0x98, 0x3a, 0x2a,
        0xc3, 0x71, 0x38, 0x31, 0x26, 0x4a, 0xdb, 0x47,
        0xfb, 0x6b, 0xd1, 0xe0, 0x58, 0xd5, 0xf0, 0x04,
    }};
};

struct Sha3_384_1600bit : Ctx384, Data1600 {
	std::vector<uint8_t> hash = {{
        0x18, 0x81, 0xde, 0x2c, 0xa7, 0xe4, 0x1e, 0xf9,
        0x5d, 0xc4, 0x73, 0x2b, 0x8f, 0x5f, 0x00, 0x2b,
        0x18, 0x9c, 0xc1, 0xe4, 0x2b, 0x74, 0x16, 0x8e,
        0xd1, 0x73, 0x26, 0x49, 0xce, 0x1d, 0xbc, 0xdd,
        0x76, 0x19, 0x7a, 0x31, 0xfd, 0x55, 0xee, 0x98,
        0x9f, 0x2d, 0x70, 0x50, 0xdd, 0x47, 0x3e, 0x8f
    }};
};

struct Sha3_384_8000000bit : Ctx384, Data8000000 {
	std::vector<uint8_t> hash = {{
        0xee, 0xe9, 0xe2, 0x4d, 0x78, 0xc1, 0x85, 0x53,
        0x37, 0x98, 0x34, 0x51, 0xdf, 0x97, 0xc8, 0xad,
        0x9e, 0xed, 0xf2, 0x56, 0xc6, 0x33, 0x4f, 0x8e,
        0x94, 0x8d, 0x25, 0x2d, 0x5e, 0x0e, 0x76, 0x84,
        0x7a, 0xa0, 0x77, 0x4d, 0xdb, 0x90, 0xa8, 0x42,
        0x19, 0x0d, 0x2c, 0x55, 0x8b, 0x4b, 0x83, 0x40,
    }};
};

struct Sha3_512_0bit : Ctx512, Data0 {
	std::vector<uint8_t> hash = {{
        0xa6, 0x9f, 0x73, 0xcc, 0xa2, 0x3a, 0x9a, 0xc5,
        0xc8, 0xb5, 0x67, 0xdc, 0x18, 0x5a, 0x75, 0x6e,
        0x97, 0xc9, 0x82, 0x16, 0x4f, 0xe2, 0x58, 0x59,
        0xe0, 0xd1, 0xdc, 0xc1, 0x47, 0x5c, 0x80, 0xa6,
        0x15, 0xb2, 0x12, 0x3a, 0xf1, 0xf5, 0xf9, 0x4c,
        0x11, 0xe3, 0xe9, 0x40, 0x2c, 0x3a, 0xc5, 0x58,
        0xf5, 0x00, 0x19, 0x9d, 0x95, 0xb6, 0xd3, 0xe3,
        0x01, 0x75, 0x85, 0x86, 0x28, 0x1d, 0xcd, 0x26,
    }};
};

struct Sha3_512_1600bit : Ctx512, Data1600 {
	std::vector<uint8_t> hash = {{
        0xe7, 0x6d, 0xfa, 0xd2, 0x20, 0x84, 0xa8, 0xb1,
        0x46, 0x7f, 0xcf, 0x2f, 0xfa, 0x58, 0x36, 0x1b,
        0xec, 0x76, 0x28, 0xed, 0xf5, 0xf3, 0xfd, 0xc0,
        0xe4, 0x80, 0x5d, 0xc4, 0x8c, 0xae, 0xec, 0xa8,
        0x1b, 0x7c, 0x13, 0xc3, 0x0a, 0xdf, 0x52, 0xa3,
        0x65, 0x95, 0x84, 0x73, 0x9a, 0x2d, 0xf4, 0x6b,
        0xe5, 0x89, 0xc5, 0x1c, 0xa1, 0xa4, 0xa8, 0x41,
        0x6d, 0xf6, 0x54, 0x5a, 0x1c, 0xe8, 0xba, 0x00
    }};
};

struct Sha3_512_8000000bit : Ctx512, Data8000000 {
	std::vector<uint8_t> hash = {{
        0x3c, 0x3a, 0x87, 0x6d, 0xa1, 0x40, 0x34, 0xab,
        0x60, 0x62, 0x7c, 0x07, 0x7b, 0xb9, 0x8f, 0x7e,
        0x12, 0x0a, 0x2a, 0x53, 0x70, 0x21, 0x2d, 0xff,
        0xb3, 0x38, 0x5a, 0x18, 0xd4, 0xf3, 0x88, 0x59,
        0xed, 0x31, 0x1d, 0x0a, 0x9d, 0x51, 0x41, 0xce,
        0x9c, 0xc5, 0xc6, 0x6e, 0xe6, 0x89, 0xb2, 0x66,
        0xa8, 0xaa, 0x18, 0xac, 0xe8, 0x28, 0x2a, 0x0e,
        0x0d, 0xb5, 0x96, 0xc9, 0x0b, 0x0a, 0x7b, 0x87,
    }};
};

typedef ::testing::Types<Sha3_224_0bit,
                         Sha3_224_1600bit,
                         Sha3_224_8000000bit,
                         Sha3_256_0bit,
                         Sha3_256_1600bit,
                         Sha3_256_8000000bit,
                         Sha3_384_0bit,
                         Sha3_384_1600bit,
                         Sha3_384_8000000bit,
                         Sha3_512_0bit,
                         Sha3_512_1600bit,
                         Sha3_512_8000000bit> ShaTests;

TYPED_TEST_CASE(Sha3Test, ShaTests);

TYPED_TEST(Sha3Test, OneStep)
{
    TypeParam param;
    param.ctx.update(param.data.data(), param.data.size());
    auto hash = param.ctx.finalize();
    EXPECT_EQ_MEM(param.hash.data(), hash.data(), param.hash.size());
}

TYPED_TEST(Sha3Test, TwoSteps)
{
    TypeParam param;
    std::size_t firstChunk = param.data.size() / 2;
    std::size_t secondChunk = param.data.size() - firstChunk;
    param.ctx.update(param.data.data(), firstChunk);
    param.ctx.update(param.data.data() + firstChunk, secondChunk);
    auto hash = param.ctx.finalize();
    EXPECT_EQ_MEM(param.hash.data(), hash.data(), param.hash.size());
}

TYPED_TEST(Sha3Test, ByteByByte)
{
    TypeParam param;
    for (std::size_t i = 0; i < param.data.size(); i++) {
        param.ctx.update(param.data.data() + i, 1);
    }
    auto hash = param.ctx.finalize();
    EXPECT_EQ_MEM(param.hash.data(), hash.data(), param.hash.size());
}

TEST(Sha3OneStepTest, Sha3_512_1600bit)
{
    Sha3_512_1600bit testData;
    Buffer hash = Sha3<512>::calcInOneStep(testData.data);
    EXPECT_EQ(testData.hash, Bytes(hash));
}
