#include "gtest/gtest.h"
#include "TestUtils.h"

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
        StereoSample expected {0.0f, 0.0f};

        output = sut.Calculate(input);

        EXPECT_EQ(output, expected);
    }

    TEST_F(HyperbolicTangentTest, operator_inputOnes_returnsOnes){
        StereoSample input {1.0f, 1.0f};
        StereoSample expected {1.0f, 1.0f};

        output = sut.Calculate(input);

        EXPECT_EQ(output, expected);
    }

    TEST_F(HyperbolicTangentTest, operator_correctInput_returnsCorrectNormalizedTanh){
        StereoSample input {0.5f, 0.5f};
        StereoSample expected {
            static_cast<float>(std::tanh(0.5f) / std::tanh(1)),
            static_cast<float>(std::tanh(0.5f) / std::tanh(1))
        };

        output = sut.Calculate(input);

        EXPECT_EQ(output, expected);
    }

    TEST_F(HyperbolicTangentTest, operator_correctInputWithGain_returnsCorrectNormalizedTanh){
        StereoSample input {0.5f, 0.5f};
        StereoSample expected {
            static_cast<float>(std::tanh(2 * 0.5f) / std::tanh(2)),
            static_cast<float>(std::tanh(2 * 0.5f) / std::tanh(2))
        };

        sut.SetGain(2.0f);
        output = sut.Calculate(input);

        EXPECT_EQ(output, expected);
    }

    TEST_F(HyperbolicTangentTest, operator_correctInputWithMaxValue_returnsMaxValue){
        const float maxValue = 0.5f;
        StereoSample input {1.0f, 1.0f};
        StereoSample expected {maxValue, maxValue};

        sut.SetMaxValue(maxValue);
        output = sut.Calculate(input);

        EXPECT_EQ(output, expected);
    }

    TEST_F(HyperbolicTangentTest, operator_correctInputWithMinValue_returnsMinValue){
        const float minValue = -0.5f;
        StereoSample input {-1.0f, -1.0f};
        StereoSample expected {minValue, minValue};

        sut.SetMinValue(minValue);
        output = sut.Calculate(input);

        EXPECT_EQ(output, expected);
    }

    TEST_F(HyperbolicTangentTest, operator_correctInputWithGainZeros_returnsZeros){
        StereoSample input {0.0f, 0.0f};
        StereoSample expected {0.0f, 0.0f};

        sut.SetGain(0.0f);
        output = sut.Calculate(input);

        EXPECT_EQ(output, expected);
    }

} // namespace
