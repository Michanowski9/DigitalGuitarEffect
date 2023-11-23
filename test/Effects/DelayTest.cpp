#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "TestUtils.h"

#include "Effects/IEffect.h"
#include "Effects/delay.h"
#include "Effects/delay.cpp"

#include <cmath>
#include <ostream>

namespace {
    class DelayTest : public testing::Test
    {
    protected:
        std::shared_ptr<Settings> settings;
        Delay sut;

        // runs before each test
        void SetUp() override
        {
            settings = std::make_shared<Settings>();
            sut = Delay();
            sut.SetSettings(settings);
        }
    };

    std::vector<StereoSample> GetNanArray(size_t size){
        std::vector<StereoSample> result;
        for (size_t i = 0; i < size; i++) {
            result.push_back({ std::nanf(" "), std::nanf(" ") });
        }
        return result;
    }

    TEST(TestUtils, GetNanArray_generateCorrectData)
    {
        auto output = GetNanArray(3);

        EXPECT_TRUE(std::isnan(output[0].left));
        EXPECT_TRUE(std::isnan(output[0].right));
        EXPECT_TRUE(std::isnan(output[1].left));
        EXPECT_TRUE(std::isnan(output[1].right));
        EXPECT_TRUE(std::isnan(output[2].left));
        EXPECT_TRUE(std::isnan(output[2].right));
    }

    std::vector<StereoSample> GetInputArray(size_t size){
        std::vector<StereoSample> result;
        for (size_t i = 0; i < size; i++) {
            result.push_back({
                    static_cast<float>(i + 1)/10,
                    - static_cast<float>(i + 1)/10
                    });
        }
        return result;
    }

    TEST(TestUtils, GetInputArray_generateCorrectData)
    {
        StereoSample expected[] = {
             { 0.1f, -0.1f },
             { 0.2f, -0.2f },
             { 0.3f, -0.3f }
        };

        auto output = GetInputArray(3);

        EXPECT_THAT(output, testing::ElementsAreArray(expected));
    }

    TEST_F(DelayTest, operator_effectIsOff_returnsInput)
    {
        StereoSample output = { std::nanf(" "), std::nanf(" ") };
        StereoSample input = { 0.5f, -0.5f };

        sut.SetOn(false);
        sut(output, input);

        EXPECT_EQ(output, input);
    }

    TEST_F(DelayTest, operator_addingToBufforWithSize1_correctlyAddBufforedSignal)
    {
        auto output = GetNanArray(3);
        auto input = GetInputArray(3);
        StereoSample expected[] = {
            { input[0] },
            { input[1] + input[0] },
            { input[2] + input[1] }
        };
        settings->SetCurrentSampleRate(1);
        sut.SetDelayInMilliseconds(1000);
        sut.SetOn(true);


        sut(output[0], input[0]);
        sut(output[1], input[1]);
        sut(output[2], input[2]);


        EXPECT_THAT(output, testing::ElementsAreArray(expected));
    }

    TEST_F(DelayTest, operator_addingToBufforWithSize2_correctlyAddBufforedSignal)
    {
        auto output = GetNanArray(5);
        auto input = GetInputArray(5);
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


        sut(output[0], input[0]);
        sut(output[1], input[1]);
        sut(output[2], input[2]);
        sut(output[3], input[3]);
        sut(output[4], input[4]);


        EXPECT_THAT(output, testing::ElementsAreArray(expected));
    }

    TEST_F(DelayTest, operator_addingToBufforWithSize2SetOnDuringCalculating_correctlyAddBufforedSignal)
    {
        auto output = GetNanArray(5);
        auto input = GetInputArray(5);
        StereoSample expected[] = {
            { input[0] },
            { input[1] },
            { input[2] }, // set of after this probe
            { input[3] + input[1] },
            { input[4] + input[2] }
        };
        settings->SetCurrentSampleRate(1);
        sut.SetDelayInMilliseconds(2000);


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
        float alpha = 0.5f;
        auto output = GetNanArray(3);
        auto input = GetInputArray(5);
        StereoSample expected[] = {
            { input[0] },
            { input[1] + input[0] * alpha },
            { input[2] + input[1] * alpha }
        };
        settings->SetCurrentSampleRate(1);
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
        settings->SetCurrentSampleRate(1);
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
        //GTEST_SKIP() << "skipped - a static variable make this test depends on another test";
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
        settings->SetCurrentSampleRate(1);
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
        settings->SetCurrentSampleRate(1);
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
