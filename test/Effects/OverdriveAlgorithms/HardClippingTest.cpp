#pragma once
#include "gtest/gtest.h"

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

        sut(output, input);

        EXPECT_FLOAT_EQ(output.left, 0);
        EXPECT_FLOAT_EQ(output.right, 0);
    }

    TEST_F(HardClippingTest, operator_inputOnes_returnsOnes){
        StereoSample input {1.0f, 1.0f};

        sut(output, input);

        EXPECT_FLOAT_EQ(output.left, 1.0f);
        EXPECT_FLOAT_EQ(output.right, 1.0f);
    }

    TEST_F(HardClippingTest, operator_inputWithGainEqOne_returnsOnes){
        StereoSample input {0.5f, 0.5f};

        sut.SetGain(2.0f);
        sut(output, input);

        EXPECT_FLOAT_EQ(output.left, 1.0f);
        EXPECT_FLOAT_EQ(output.right, 1.0f);
    }

    TEST_F(HardClippingTest, operator_inputWithGainAboveOne_returnsOnes){
        StereoSample input {0.5f, 0.5f};

        sut.SetGain(3.0f);
        sut(output, input);

        EXPECT_FLOAT_EQ(output.left, 1.0f);
        EXPECT_FLOAT_EQ(output.right, 1.0f);
    }

    TEST_F(HardClippingTest, operator_inputWithGainBelowMinusOne_returnsOnes){
        StereoSample input {-0.5f, -0.5f};

        sut.SetGain(3.0f);
        sut(output, input);

        EXPECT_FLOAT_EQ(output.left, -1.0f);
        EXPECT_FLOAT_EQ(output.right, -1.0f);
    }

    TEST_F(HardClippingTest, operator_inputWithGainAboveMax_returnsOnes){
        StereoSample input {0.5f, 0.5f};
        const float maxValue = 0.5f;

        sut.SetMaxValue(maxValue);
        sut.SetGain(3.0f);
        sut(output, input);

        EXPECT_FLOAT_EQ(output.left, maxValue);
        EXPECT_FLOAT_EQ(output.right, maxValue);
    }

    TEST_F(HardClippingTest, operator_inputWithGainBelowMin_returnsOnes){
        StereoSample input {-0.5f, -0.5f};
        const float minValue = -0.5f;

        sut.SetMinValue(minValue);
        sut.SetGain(3.0f);
        sut(output, input);

        EXPECT_FLOAT_EQ(output.left, minValue);
        EXPECT_FLOAT_EQ(output.right, minValue);
    }

} // namespace
