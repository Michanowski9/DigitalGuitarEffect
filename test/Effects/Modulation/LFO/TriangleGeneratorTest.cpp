#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "TestUtils.h"

#include <cmath>
#include <memory>
#include "Settings.h"
#include "Effects/Modulation/LFO/TriangleGenerator.h"

namespace {

    class TriangleGeneratorTest : public testing::Test
    {
    protected:
        auto GetSut(){
            return 0;
        }
    };

    TEST_F(TriangleGeneratorTest, GetNextValue_smallSampleRate_correctSignal)
    {
        auto settings = std::make_shared<Settings>();
        auto sut = Modulation::TriangleGenerator(settings);
        settings->SetCurrentSampleRate(8);

        float output[12];

        for (size_t i = 0; i < 12; i++) {
            output[i] = sut.GetNextValue();
        }

        EXPECT_FLOAT_EQ(output[0], 0.0f);
        EXPECT_FLOAT_EQ(output[1], 0.5f);
        EXPECT_FLOAT_EQ(output[2], 1.0f);
        EXPECT_FLOAT_EQ(output[3], 0.5f);
        EXPECT_FLOAT_EQ(output[4], 0.0f);
        EXPECT_FLOAT_EQ(output[5], -0.5f);
        EXPECT_FLOAT_EQ(output[6], -1.0f);
        EXPECT_FLOAT_EQ(output[7], -0.5f);
        EXPECT_FLOAT_EQ(output[8], 0.0f);
        EXPECT_FLOAT_EQ(output[9], 0.5f);
        EXPECT_FLOAT_EQ(output[10], 1.0f);
        EXPECT_FLOAT_EQ(output[11], 0.5f);
    }

    TEST_F(TriangleGeneratorTest, GetNextValue_smallSampleRate2Hz_correctSignal)
    {
        auto settings = std::make_shared<Settings>();
        auto sut = Modulation::TriangleGenerator(settings);
        settings->SetCurrentSampleRate(8);
        float output[12];

        sut.SetFrequency(2.0f);

        for (size_t i = 0; i < 12; i++) {
            output[i] = sut.GetNextValue();
        }

        EXPECT_FLOAT_EQ(output[0], 0.0f);
        EXPECT_FLOAT_EQ(output[1], 1.0f);
        EXPECT_FLOAT_EQ(output[2], 0.0f);
        EXPECT_FLOAT_EQ(output[3], -1.0f);
        EXPECT_FLOAT_EQ(output[4], 0.0f);
        EXPECT_FLOAT_EQ(output[5], 1.0f);
        EXPECT_FLOAT_EQ(output[6], 0.0f);
        EXPECT_FLOAT_EQ(output[7], -1.0f);
        EXPECT_FLOAT_EQ(output[8], 0.0f);
        EXPECT_FLOAT_EQ(output[9], 1.0f);
        EXPECT_FLOAT_EQ(output[10], 0.0f);
        EXPECT_FLOAT_EQ(output[11], -1.0f);
    }

} // namespace
