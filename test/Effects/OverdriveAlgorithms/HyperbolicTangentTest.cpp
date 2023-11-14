#pragma once
#include "gtest/gtest.h"

#include "Effects/OverdriveAlgorithms/HyperbolicTangent.h"

#include <cmath>

namespace {

    class HyperbolicTangentTest : public testing::Test
    {
    protected:
        HyperbolicTangent sut;
        StereoSample output;

        // runs before each test
        void SetUp() override
        {
            sut = HyperbolicTangent();
            output = {
                std::nanf(" "),
                std::nanf(" ")
            };
        }
    };

    TEST_F(HyperbolicTangentTest, operator_inputZeros_returnsZero){
        StereoSample input {0.0f, 0.0f};

        sut(output, input);

        EXPECT_FLOAT_EQ(output.left, 0);
        EXPECT_FLOAT_EQ(output.right, 0);
    }

    TEST_F(HyperbolicTangentTest, operator_inputOnes_returnsOnes){
        StereoSample input {1.0f, 1.0f};

        sut(output, input);

        EXPECT_FLOAT_EQ(output.left, 1.0f);
        EXPECT_FLOAT_EQ(output.right, 1.0f);
    }

    TEST_F(HyperbolicTangentTest, operator_correctInput_returnsCorrectNormalizedTanh){
        StereoSample input {0.5f, 0.5f};

        sut(output, input);

        EXPECT_FLOAT_EQ(output.left, std::tanh(0.5f) / std::tanh(1));
        EXPECT_FLOAT_EQ(output.right, std::tanh(0.5f) / std::tanh(1));
    }

    TEST_F(HyperbolicTangentTest, operator_correctInputWithGain_returnsCorrectNormalizedTanh){
        StereoSample input {0.5f, 0.5f};

        sut.SetGain(2.0f);
        sut(output, input);

        EXPECT_FLOAT_EQ(output.left, std::tanh(2 * 0.5f) / std::tanh(2));
        EXPECT_FLOAT_EQ(output.right, std::tanh(2 * 0.5f) / std::tanh(2));
    }

    TEST_F(HyperbolicTangentTest, operator_correctInputWithMaxValue_returnsMaxValue){
        StereoSample input {1.0f, 1.0f};
        const float maxValue = 0.5f;

        sut.SetMaxValue(maxValue);
        sut(output, input);

        EXPECT_FLOAT_EQ(output.left, maxValue);
        EXPECT_FLOAT_EQ(output.right, maxValue);
    }

    TEST_F(HyperbolicTangentTest, operator_correctInputWithMinValue_returnsMinValue){
        StereoSample input {-1.0f, -1.0f};
        const float minValue = -0.5f;

        sut.SetMinValue(minValue);
        sut(output, input);

        EXPECT_FLOAT_EQ(output.left, minValue);
        EXPECT_FLOAT_EQ(output.right, minValue);
    }

    TEST_F(HyperbolicTangentTest, operator_correctInputWithGainZeros_returnsZeros){
        StereoSample input {0.0f, 0.0f};

        sut.SetGain(0.0f);
        sut(output, input);

        EXPECT_FLOAT_EQ(output.left, 0.0f);
        EXPECT_FLOAT_EQ(output.right, 0.0f);
    }

} // namespace
