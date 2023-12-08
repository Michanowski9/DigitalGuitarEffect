#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "TestUtils.h"

#include "Effects/OverdriveAlgorithms/IOverdriveAlgorithm.h"
#include "Effects/overdrive.h"
#include "Effects/overdrive.cpp"

#include <cmath>

namespace {

    class OverdriveAlgorithmMock : public IOverdriveAlgorithm
    {
    public:
        MOCK_METHOD(StereoSample, Calculate, (const StereoSample& input), (override));
        MOCK_METHOD(std::string, GetName, (), (override));
        MOCK_METHOD(void, SetGain, (const float value), (override));
        MOCK_METHOD(bool, IsUsingGain, (), (override));
        MOCK_METHOD(void, SetMinValue, (const float value), (override));
        MOCK_METHOD(bool, IsUsingMinValue, (), (override));
        MOCK_METHOD(void, SetMaxValue, (const float value), (override));
        MOCK_METHOD(bool, IsUsingMaxValue, (), (override));
    };

    class OverdriveTest : public testing::Test
    {
    protected:
        Overdrive sut;
        StereoSample output;

        // runs before each test
        void SetUp() override
        {
            sut = Overdrive();
            output = {
                std::nanf(" "),
                std::nanf(" ")
            };
        }
    };

    TEST_F(OverdriveTest, Calculate_effectIsOff_returnsInput){
        const StereoSample input = { 0.5f, -0.5f };

        sut.SetOn(false);
        sut(output, input);

        EXPECT_EQ(output, input);
    }

    TEST_F(OverdriveTest, Calculate_effectISOn_returnsModulatedInput){
        const StereoSample input = { 0.5f, -0.5f };
        const StereoSample expected = { 1.0f, -1.0f };
        auto algorithm = std::make_shared<OverdriveAlgorithmMock>();
        sut.AddAlgorithm(algorithm);

        EXPECT_CALL(*algorithm, Calculate(input))
            .Times(1)
            .WillOnce(testing::Return(expected));

        sut.SetOn(true);
        sut(output, input);

        EXPECT_EQ(output, expected);
    }

    TEST_F(OverdriveTest, Calculate_inputWithSecondAlgorithmWhenEffectOn_returnsCorrectModulatedInput){
        const StereoSample input = { 0.5f, -0.5f };
        const StereoSample expected = { 1.0f, -1.0f };

        auto algorithm1 = std::make_shared<OverdriveAlgorithmMock>();
        auto algorithm2 = std::make_shared<OverdriveAlgorithmMock>();
        EXPECT_CALL(*algorithm2, Calculate(input))
            .Times(1)
            .WillOnce(testing::Return(expected));

        sut.AddAlgorithm(algorithm1);
        sut.AddAlgorithm(algorithm2);

        sut.SetAlgorithm(1);
        sut.SetOn(true);
        sut(output, input);

        EXPECT_EQ(output, expected);
    }

    TEST_F(OverdriveTest, SetGain_algorithmIsUsingGain_callsSetGain){
        auto algorithm = std::make_shared<OverdriveAlgorithmMock>();
        auto gainValue = 5.0f;

        EXPECT_CALL(*algorithm, IsUsingGain())
            .Times(1)
            .WillOnce(testing::Return(true));
        EXPECT_CALL(*algorithm, SetGain(gainValue))
            .Times(1);

        sut.AddAlgorithm(algorithm);

        sut.SetGain(gainValue);
    }

    TEST_F(OverdriveTest, SetGain_algorithmIsNotUsingGain_doNothing){
        auto algorithm = std::make_shared<OverdriveAlgorithmMock>();
        auto gainValue = 5.0f;

        EXPECT_CALL(*algorithm, IsUsingGain())
            .Times(1)
            .WillOnce(testing::Return(false));
        EXPECT_CALL(*algorithm, SetGain(gainValue))
            .Times(0);

        sut.AddAlgorithm(algorithm);

        sut.SetGain(gainValue);
    }

    TEST_F(OverdriveTest, SetGain_multipleAlgorithms_callsSetGainInAlgorithmsThatImplementsGain){
        std::shared_ptr<OverdriveAlgorithmMock> algorithms[] = {
            std::make_shared<OverdriveAlgorithmMock>(),
            std::make_shared<OverdriveAlgorithmMock>(),
            std::make_shared<OverdriveAlgorithmMock>()
        };
        auto gainValue = 5.0f;

        EXPECT_CALL(*algorithms[0], IsUsingGain())
            .Times(1)
            .WillOnce(testing::Return(false));
        EXPECT_CALL(*algorithms[0], SetGain(gainValue))
            .Times(0);

        EXPECT_CALL(*algorithms[1], IsUsingGain())
            .Times(1)
            .WillOnce(testing::Return(true));
        EXPECT_CALL(*algorithms[1], SetGain(gainValue))
            .Times(1);

        EXPECT_CALL(*algorithms[2], IsUsingGain())
            .Times(1)
            .WillOnce(testing::Return(true));
        EXPECT_CALL(*algorithms[2], SetGain(gainValue))
            .Times(1);

        sut.AddAlgorithm(algorithms[0]);
        sut.AddAlgorithm(algorithms[1]);
        sut.AddAlgorithm(algorithms[2]);

        sut.SetGain(gainValue);
    }

    TEST_F(OverdriveTest, SetMinValue_twoAlgorihtms_setsIfUsing){
        std::shared_ptr<OverdriveAlgorithmMock> algorithms[] = {
            std::make_shared<OverdriveAlgorithmMock>(),
            std::make_shared<OverdriveAlgorithmMock>()
        };
        auto minValue = -0.5f;

        EXPECT_CALL(*algorithms[0], IsUsingMinValue())
            .Times(1)
            .WillOnce(testing::Return(false));
        EXPECT_CALL(*algorithms[0], SetMinValue(minValue))
            .Times(0);

        EXPECT_CALL(*algorithms[1], IsUsingMinValue())
            .Times(1)
            .WillOnce(testing::Return(true));
        EXPECT_CALL(*algorithms[1], SetMinValue(minValue))
            .Times(1);

        sut.AddAlgorithm(algorithms[0]);
        sut.AddAlgorithm(algorithms[1]);

        sut.SetMinValue(minValue);
    }

    TEST_F(OverdriveTest, SetMaxValue_twoAlgorithms_setsIfUsing){
        std::shared_ptr<OverdriveAlgorithmMock> algorithms[] = {
            std::make_shared<OverdriveAlgorithmMock>(),
            std::make_shared<OverdriveAlgorithmMock>()
        };
        auto maxValue = 0.5f;

        EXPECT_CALL(*algorithms[0], IsUsingMaxValue())
            .Times(1)
            .WillOnce(testing::Return(false));
        EXPECT_CALL(*algorithms[0], SetMaxValue(maxValue))
            .Times(0);

        EXPECT_CALL(*algorithms[1], IsUsingMaxValue())
            .Times(1)
            .WillOnce(testing::Return(true));
        EXPECT_CALL(*algorithms[1], SetMaxValue(maxValue))
            .Times(1);

        sut.AddAlgorithm(algorithms[0]);
        sut.AddAlgorithm(algorithms[1]);

        sut.SetMaxValue(maxValue);
    }
} // namespace
