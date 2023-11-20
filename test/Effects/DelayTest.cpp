#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "TestUtils.h"

#include "Effects/IEffect.h"
#include "Effects/delay.h"
#include "Effects/delay.cpp"

#include <cmath>

namespace {

    class DelayTest : public testing::Test
    {
    protected:
        std::shared_ptr<Settings> settings;
        Delay sut;
        StereoSample output;

        // runs before each test
        void SetUp() override
        {
            settings = std::make_shared<Settings>();
            sut = Delay();
            sut.SetSettings(settings);

            output = {
                std::nanf(" "),
                std::nanf(" ")
            };
        }
    };

    TEST_F(DelayTest, operator_effectIsOff_returnsInput)
    {
        StereoSample input = { 0.5f, -0.5f };

        sut.SetOn(false);
        sut(output, input);

        EXPECT_STEREOSAMPLE_EQ(output, input);
    }

    TEST_F(DelayTest, operator_addingToBufforWithSize1_correctlyAddBufforedSignal)
    {
        StereoSample input[] = {
            {0.10f, -0.10f},
            {0.20f, -0.20f},
            {0.30f, -0.30f}
        };
        StereoSample expected[] = {
            { input[0] },
            { input[1] + input[0] },
            { input[2] + input[1] }
        };
        settings->SetCurrentSampleRate(1);
        sut.SetDelayInMilliseconds(1000);

        sut.SetOn(true);

        sut(output, input[0]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[0]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut(output, input[1]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[1]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut(output, input[2]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[2]);
    }

    TEST_F(DelayTest, operator_addingToBufforWithSize2_correctlyAddBufforedSignal)
    {
        StereoSample input[] = {
            {0.10f, -0.10f},
            {0.20f, -0.20f},
            {0.30f, -0.30f},
            {0.40f, -0.40f},
            {0.50f, -0.50f}
        };
        StereoSample expected[] = {
            { input[0] },
            { input[1] },
            { input[2] + input[0] },
            { input[3] + input[1] },
            { input[4] + input[2] }
        };
        settings->SetCurrentSampleRate(1);
        sut.SetDelayInMilliseconds(2000);

        sut.SetOn(true);

        sut(output, input[0]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[0]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut(output, input[1]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[1]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut(output, input[2]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[2]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut(output, input[3]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[3]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut(output, input[4]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[4]);
    }

    TEST_F(DelayTest, operator_addingToBufforWithSize2SetOnDuringCalculating_correctlyAddBufforedSignal)
    {
        StereoSample input[] = {
            {0.10f, -0.10f},
            {0.20f, -0.20f},
            {0.30f, -0.30f},
            {0.40f, -0.40f},
            {0.50f, -0.50f}
        };
        StereoSample expected[] = {
            { input[0] },
            { input[1] },
            { input[2] }, // set of after this probe
            { input[3] + input[1] },
            { input[4] + input[2] }
        };
        settings->SetCurrentSampleRate(1);
        sut.SetDelayInMilliseconds(2000);


        sut(output, input[0]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[0]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut(output, input[1]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[1]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut(output, input[2]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[2]);

        sut.SetOn(true);

        output = { std::nanf(" "), std::nanf(" ") };
        sut(output, input[3]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[3]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut(output, input[4]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[4]);
    }

    TEST_F(DelayTest, operator_addingToBufforWithAlphaNotEq1_correctlyAddBufforedScaledSignal)
    {
        float alpha = 0.5f;
        StereoSample input[] = {
            {0.10f, -0.10f},
            {0.20f, -0.20f},
            {0.30f, -0.30f}
        };
        StereoSample expected[] = {
            { input[0] },
            { input[1] + input[0] * alpha },
            { input[2] + input[1] * alpha }
        };
        settings->SetCurrentSampleRate(1);
        sut.SetDelayInMilliseconds(1000);

        sut.SetAlpha(alpha);
        sut.SetOn(true);

        sut(output, input[0]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[0]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut(output, input[1]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[1]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut(output, input[2]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[2]);
    }

    TEST_F(DelayTest, CalculateForVisualization_correctInput_correctOutput)
    {
        auto alpha = 0.5f;
        StereoSample input[] = {
            {0.10f, -0.10f},
            {0.20f, -0.20f},
            {0.30f, -0.30f},
            {0.40f, -0.40f},
            {0.50f, -0.50f}
        };
        StereoSample expected[] = {
            { input[0] },
            { input[1] },
            { input[2] + input[0] * alpha },
            { input[3] + input[1] * alpha },
            { input[4] + input[2] * alpha }
        };
        settings->SetCurrentSampleRate(1);
        sut.SetDelayInMilliseconds(2);
        sut.SetAlpha(alpha);


        output = { std::nanf(" "), std::nanf(" ") };
        sut.CalculateForVisualization(output, input[0]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[0]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut.CalculateForVisualization(output, input[1]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[1]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut.CalculateForVisualization(output, input[2]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[2]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut.CalculateForVisualization(output, input[3]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[3]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut.CalculateForVisualization(output, input[4]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[4]);
    }

    TEST_F(DelayTest, CalculateForVisualization_audioMixedWithVisualization_correctOutput)
    {
        GTEST_SKIP() << "skipped - a static variable make this test depends on another test";
        constexpr auto alpha = 0.5f;
        StereoSample input[] = {
            {0.10f, -0.10f},
            {0.20f, -0.20f},
            {0.30f, -0.30f},
            {0.40f, -0.40f},
            {0.50f, -0.50f}
        };
        StereoSample expected[] = {
            { input[0] },
            { input[1] },
            { input[2] + input[0] * alpha },
            { input[3] + input[1] * alpha },
            { input[4] + input[2] * alpha }
        };
        settings->SetCurrentSampleRate(1);
        sut.SetDelayInMilliseconds(2);
        sut.SetAlpha(alpha);
        sut.SetOn(true);

        output = { std::nanf(" "), std::nanf(" ") };
        sut.CalculateForVisualization(output, input[0]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[0]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut.CalculateForVisualization(output, input[1]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[1]);

        StereoSample temp{ 0, 0 };
        sut(temp, temp);
        sut(temp, temp);
        sut(temp, temp);

        output = { std::nanf(" "), std::nanf(" ") };
        sut.CalculateForVisualization(output, input[2]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[2]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut.CalculateForVisualization(output, input[3]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[3]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut.CalculateForVisualization(output, input[4]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[4]);
    }

    TEST_F(DelayTest, operator_audioMixedWithVisualization_correctOutput)
    {
        constexpr auto alpha = 0.5;
        StereoSample input[] = {
            {0.10f, -0.10f},
            {0.20f, -0.20f},
            {0.30f, -0.30f},
            {0.40f, -0.40f},
            {0.50f, -0.50f}
        };
        StereoSample expected[] = {
            { input[0] },
            { input[1] },
            { input[2] + input[0] * alpha },
            { input[3] + input[1] * alpha },
            { input[4] + input[2] * alpha }
        };
        settings->SetCurrentSampleRate(1);
        sut.SetDelayInMilliseconds(2000);
        sut.SetAlpha(alpha);
        sut.SetOn(true);

        sut(output, input[0]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[0]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut(output, input[1]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[1]);

        StereoSample temp { 0, 0 };
        sut.CalculateForVisualization(temp,temp);
        sut.CalculateForVisualization(temp,temp);
        sut.CalculateForVisualization(temp,temp);

        output = { std::nanf(" "), std::nanf(" ") };
        sut(output, input[2]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[2]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut(output, input[3]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[3]);

        output = { std::nanf(" "), std::nanf(" ") };
        sut(output, input[4]);
        EXPECT_STEREOSAMPLE_EQ(output, expected[4]);
    }


} // namespace
