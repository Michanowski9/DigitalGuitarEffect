#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "TestUtils.h"

#include "Effects/IEffect.h"
#include "Effects/Chorus/Chorus.h"
#include "Effects/Chorus/Chorus.cpp"

#include <cmath>
#include <memory>

namespace {
/*    class ChorusTest : public testing::Test
    {
    protected:
        // runs before each test
        void SetUp() override
        {
        }

        auto GetSut(){
            auto settings = std::make_shared<Settings>();
            auto result = Chorus();

            settings->SetCurrentSampleRate(1);

            result.SetSettings(settings);
            return result;
        }
    };

    TEST_F(ChorusTest, operator_effectIsOff_returnsInput)
    {
        auto sut = GetSut();
        StereoSample output = { std::nanf(" "), std::nanf(" ") };
        StereoSample input = { 0.5f, -0.5f };

        sut.SetOn(false);
        sut(output, input);

        EXPECT_EQ(output, input);
    }*/
} // namespace
