#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "TestUtils.h"

#include "Effects/Delay/Algorithms/RecursiveCombFilter.h"

#include <cmath>
#include <memory>

namespace {
    using namespace Delay;

    class RecursiveCombFilterTest : public testing::Test
    {

    };

    TEST_F(RecursiveCombFilterTest, Calculate_DelayGreaterThanProbesNo_returnsInput)
    {
        auto sut = RecursiveCombFilter();
        sut.SetDelay(100);
        auto input = GetInputArray(5);
        auto output = GetNanArray(5);

        output[0] = sut.Calculate(input[0]);
        sut.AddToBuffor(input[0]);
        output[1] = sut.Calculate(input[1]);
        sut.AddToBuffor(input[1]);
        output[2] = sut.Calculate(input[2]);
        sut.AddToBuffor(input[2]);
        output[3] = sut.Calculate(input[3]);
        sut.AddToBuffor(input[3]);
        output[4] = sut.Calculate(input[4]);
        sut.AddToBuffor(input[4]);

        EXPECT_THAT(output, testing::ElementsAreArray(input));
    }

    TEST_F(RecursiveCombFilterTest, Calculate_smallBuffor_outputWithOneEcho)
    {
        auto sut = RecursiveCombFilter();
        sut.SetDelay(3);
        auto alpha = 0.5f;
        sut.SetAlpha(alpha);
        auto input = GetInputArray(5);
        auto output = GetNanArray(5);
        StereoSample expected[] = {
            input[0],
            input[1],
            input[2],
            input[3] + alpha * input[0],
            input[4] + alpha * input[1]
        };

        output[0] = sut.Calculate(input[0]);
        sut.AddToBuffor(input[0]);
        output[1] = sut.Calculate(input[1]);
        sut.AddToBuffor(input[1]);
        output[2] = sut.Calculate(input[2]);
        sut.AddToBuffor(input[2]);
        output[3] = sut.Calculate(input[3]);
        sut.AddToBuffor(input[3]);
        output[4] = sut.Calculate(input[4]);
        sut.AddToBuffor(input[4]);

        EXPECT_THAT(output, testing::ElementsAreArray(expected));
    }

    TEST_F(RecursiveCombFilterTest, Calculate_smallBuffor_outputWithTwoEchos)
    {
        auto sut = RecursiveCombFilter();
        sut.SetDelay(2);
        auto alpha = 0.5f;
        sut.SetAlpha(alpha);
        auto input = GetInputArray(5);
        auto output = GetNanArray(5);
        StereoSample expected[] = {
            input[0],
            input[1],
            input[2] + alpha * input[0],
            input[3] + alpha * input[1],
            input[4] + alpha * input[2] + alpha * alpha * input[0]
        };

        output[0] = sut.Calculate(input[0]);
        sut.AddToBuffor(input[0]);
        output[1] = sut.Calculate(input[1]);
        sut.AddToBuffor(input[1]);
        output[2] = sut.Calculate(input[2]);
        sut.AddToBuffor(input[2]);
        output[3] = sut.Calculate(input[3]);
        sut.AddToBuffor(input[3]);
        output[4] = sut.Calculate(input[4]);
        sut.AddToBuffor(input[4]);

        // not work due to operations on floats. To refactor (create custom assert)
        // EXPECT_THAT(output, testing::ElementsAreArray(expected));
        EXPECT_FLOAT_EQ(output[0].left, expected[0].left);
        EXPECT_FLOAT_EQ(output[0].right, expected[0].right);
        EXPECT_FLOAT_EQ(output[1].left, expected[1].left);
        EXPECT_FLOAT_EQ(output[1].right, expected[1].right);
        EXPECT_FLOAT_EQ(output[2].left, expected[2].left);
        EXPECT_FLOAT_EQ(output[2].right, expected[2].right);
        EXPECT_FLOAT_EQ(output[3].left, expected[3].left);
        EXPECT_FLOAT_EQ(output[3].right, expected[3].right);
        EXPECT_FLOAT_EQ(output[4].left, expected[4].left);
        EXPECT_FLOAT_EQ(output[4].right, expected[4].right);
    }
} // namespace
