#include "gtest/gtest.h"
#include "TestUtils.h"

#include "Effects/OverdriveAlgorithms/HardClipping.h"

#include <cmath>

namespace {

    class HardClippingTest : public testing::Test
    {
    protected:
        HardClipping sut;
        StereoSample output;

        // runs before each test
        void SetUp() override
        {
            sut = HardClipping();
            output = {
                std::nanf(" "),
                std::nanf(" ")
            };
        }
    };

    TEST_F(HardClippingTest, operator_inputZeros_returnsZero){
        StereoSample input {0.0f, 0.0f};
        StereoSample expected {0.0f, 0.0f};

        output = sut.Calculate(input);

        EXPECT_EQ(output, expected);
    }

    TEST_F(HardClippingTest, operator_inputOnes_returnsOnes){
        StereoSample input {1.0f, 1.0f};
        StereoSample expected {1.0f, 1.0f};

        output = sut.Calculate(input);

        EXPECT_EQ(output, expected);
    }

    TEST_F(HardClippingTest, operator_inputWithGainEqOne_returnsOnes){
        StereoSample input {0.5f, 0.5f};
        StereoSample expected {1.0f, 1.0f};

        sut.SetGain(2.0f);
        output = sut.Calculate(input);

        EXPECT_EQ(output, expected);
    }

    TEST_F(HardClippingTest, operator_inputWithGainAboveOne_returnsOnes){
        StereoSample input {0.5f, 0.5f};
        StereoSample expected {1.0f, 1.0f};

        sut.SetGain(3.0f);
        output = sut.Calculate(input);

        EXPECT_EQ(output, expected);
    }

    TEST_F(HardClippingTest, operator_inputWithGainBelowMinusOne_returnsOnes){
        StereoSample input {-0.5f, -0.5f};
        StereoSample expected {-1.0f, -1.0f};

        sut.SetGain(3.0f);
        output = sut.Calculate(input);

        EXPECT_EQ(output, expected);
    }

    TEST_F(HardClippingTest, operator_inputWithGainAboveMax_returnsOnes){
        const float maxValue = 0.5f;
        StereoSample input {0.5f, 0.5f};
        StereoSample expected {maxValue, maxValue};

        sut.SetMaxValue(maxValue);
        sut.SetGain(3.0f);
        output = sut.Calculate(input);

        EXPECT_EQ(output, expected);
    }

    TEST_F(HardClippingTest, operator_inputWithGainBelowMin_returnsOnes){
        const float minValue = -0.5f;
        StereoSample input {-0.5f, -0.5f};
        StereoSample expected {minValue, minValue};

        sut.SetMinValue(minValue);
        sut.SetGain(3.0f);
        output = sut.Calculate(input);

        EXPECT_EQ(output, expected);
    }

} // namespace
