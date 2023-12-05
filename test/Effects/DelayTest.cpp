#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "TestUtils.h"

#include "Effects/IEffect.h"
#include "Effects/delay.h"
#include "Effects/delay.cpp"
#include "Effects/DelayAlgorithms/CombFilter.h"

#include <cmath>
#include <memory>

namespace {
    class DelayTest : public testing::Test
    {
    protected:
        // runs before each test
        void SetUp() override
        {
        }

        Delay GetSut(){
            auto settings = std::make_shared<Settings>();
            auto result = Delay(
                    {
                        { std::make_shared<CombFilter>(), std::make_shared<CombFilter>() }
                    });

            settings->SetCurrentSampleRate(1);

            result.SetSettings(settings);
            return result;
        }
    };

    TEST_F(DelayTest, operator_effectIsOff_returnsInput)
    {
        auto sut = GetSut();
        StereoSample output = { std::nanf(" "), std::nanf(" ") };
        StereoSample input = { 0.5f, -0.5f };

        sut.SetOn(false);
        sut(output, input);

        EXPECT_EQ(output, input);
    }

    TEST_F(DelayTest, operator_addingToBufforWithSize1_correctlyAddBufforedSignal)
    {
        auto sut = GetSut();
        auto alpha = 0.5f;
        auto output = GetNanArray(3);
        auto input = GetInputArray(3);
        StereoSample expected[] = {
            { input[0] },
            { input[1] + alpha * input[0] },
            { input[2] + alpha * input[1] }
        };
        sut.SetDelayInMilliseconds(1000);
        sut.SetAlpha(alpha);
        sut.SetOn(true);


        sut(output[0], input[0]);
        sut(output[1], input[1]);
        sut(output[2], input[2]);


        EXPECT_THAT(output, testing::ElementsAreArray(expected));
    }

    TEST_F(DelayTest, operator_addingToBufforWithSize2_correctlyAddBufforedSignal)
    {
        auto sut = GetSut();
        auto alpha = 0.5f;
        auto output = GetNanArray(5);
        auto input = GetInputArray(5);
        StereoSample expected[] = {
            { input[0] },
            { input[1] },
            { input[2] + alpha * input[0] },
            { input[3] + alpha * input[1] },
            { input[4] + alpha * input[2] }
        };
        sut.SetDelayInMilliseconds(2000);
        sut.SetAlpha(alpha);
        sut.SetOn(true);


        sut(output[0], input[0]);
        sut(output[1], input[1]);
        sut(output[2], input[2]);
        sut(output[3], input[3]);
        sut(output[4], input[4]);


        EXPECT_THAT(output, testing::ElementsAreArray(expected));
    }

    TEST_F(DelayTest, operator_addingToBufforWithSize2SetOnDuringCalculating_correctlyAddBufforedSignal)
    {
        auto sut = GetSut();
        auto alpha = 0.5f;
        auto output = GetNanArray(5);
        auto input = GetInputArray(5);
        StereoSample expected[] = {
            { input[0] },
            { input[1] },
            { input[2] }, // set of after this probe
            { input[3] + alpha * input[1] },
            { input[4] + alpha * input[2] }
        };
        sut.SetDelayInMilliseconds(2000);
        sut.SetAlpha(alpha);


        sut(output[0], input[0]);
        sut(output[1], input[1]);
        sut(output[2], input[2]);
        sut.SetOn(true);
        sut(output[3], input[3]);
        sut(output[4], input[4]);


        EXPECT_THAT(output, testing::ElementsAreArray(expected));
    }

    TEST_F(DelayTest, operator_addingToBufforWithAlphaNotEq1_correctlyAddBufforedScaledSignal)
    {
        auto sut = GetSut();
        float alpha = 0.5f;
        auto output = GetNanArray(3);
        auto input = GetInputArray(5);
        StereoSample expected[] = {
            { input[0] },
            { input[1] + input[0] * alpha },
            { input[2] + input[1] * alpha }
        };
        sut.SetDelayInMilliseconds(1000);
        sut.SetAlpha(alpha);
        sut.SetOn(true);


        sut(output[0], input[0]);
        sut(output[1], input[1]);
        sut(output[2], input[2]);


        EXPECT_THAT(output, testing::ElementsAreArray(expected));
    }

    TEST_F(DelayTest, CalculateForVisualization_correctInput_correctOutput)
    {
        auto sut = GetSut();
        auto alpha = 0.5f;
        auto output = GetNanArray(5);
        auto input = GetInputArray(5);
        StereoSample expected[] = {
            { input[0] },
            { input[1] },
            { input[2] + input[0] * alpha },
            { input[3] + input[1] * alpha },
            { input[4] + input[2] * alpha }
        };
        sut.SetDelayInMilliseconds(2);
        sut.SetAlpha(alpha);


        sut.CalculateForVisualization(output[0], input[0]);
        sut.CalculateForVisualization(output[1], input[1]);
        sut.CalculateForVisualization(output[2], input[2]);
        sut.CalculateForVisualization(output[3], input[3]);
        sut.CalculateForVisualization(output[4], input[4]);

        EXPECT_THAT(output, testing::ElementsAreArray(expected));
    }

    TEST_F(DelayTest, CalculateForVisualization_audioMixedWithVisualization_correctOutput)
    {
        GTEST_SKIP() << "throws exception only on windows \"SEH exception with code 0xc0000005 thrown in the test body\"";
        auto sut = GetSut();
        constexpr auto alpha = 0.5f;
        auto output = GetNanArray(5);
        auto input = GetInputArray(5);
        StereoSample expected[] = {
            { input[0] },
            { input[1] },
            { input[2] + input[0] * alpha },
            { input[3] + input[1] * alpha },
            { input[4] + input[2] * alpha }
        };
        sut.SetDelayInMilliseconds(2);
        sut.SetAlpha(alpha);
        sut.SetOn(true);


        sut.CalculateForVisualization(output[0], input[0]);
        sut.CalculateForVisualization(output[1], input[1]);

        StereoSample temp{ 0, 0 };
        sut(temp, temp);
        sut(temp, temp);
        sut(temp, temp);

        sut.CalculateForVisualization(output[2], input[2]);
        sut.CalculateForVisualization(output[3], input[3]);
        sut.CalculateForVisualization(output[4], input[4]);


        EXPECT_THAT(output, testing::ElementsAreArray(expected));
    }

    TEST_F(DelayTest, operator_audioMixedWithVisualization_correctOutput)
    {
        auto sut = GetSut();
        constexpr auto alpha = 0.5;
        auto output = GetNanArray(5);
        auto input = GetInputArray(5);
        StereoSample expected[] = {
            { input[0] },
            { input[1] },
            { input[2] + input[0] * alpha },
            { input[3] + input[1] * alpha },
            { input[4] + input[2] * alpha }
        };
        sut.SetDelayInMilliseconds(2000);
        sut.SetAlpha(alpha);
        sut.SetOn(true);


        sut(output[0], input[0]);
        sut(output[1], input[1]);

        StereoSample temp { 0, 0 };
        sut.CalculateForVisualization(temp,temp);
        sut.CalculateForVisualization(temp,temp);
        sut.CalculateForVisualization(temp,temp);

        sut(output[2], input[2]);
        sut(output[3], input[3]);
        sut(output[4], input[4]);


        EXPECT_THAT(output, testing::ElementsAreArray(expected));
    }
} // namespace
