#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "TestUtils.h"

#include "Effects/IEffect.h"
#include "Effects/Modulation/Algorithms/Chorus.h"

#include <cmath>
#include <memory>

namespace {

    class LFOMock : public ILFO {
    public:
        MOCK_METHOD(float, GetNextValue, (), (override));
        MOCK_METHOD(void, SetFrequency, (const float), (override));
        MOCK_METHOD(void, ResetCounter, (), (override));
    };

    class ChorusTest : public testing::Test
    {
    protected:
    };

    TEST_F(ChorusTest, LinearInterpolation_1)
    {
        auto sut = Chorus();
        auto output = sut.LinearInterpolation(0.5f, {1,1}, {2,2});
        EXPECT_FLOAT_EQ(output.left, 1.5f);
        EXPECT_FLOAT_EQ(output.right, 1.5f);
    }

    TEST_F(ChorusTest, LinearInterpolation_2)
    {
        auto sut = Chorus();
        auto output = sut.LinearInterpolation(0.25f, {1,1}, {2,2});
        EXPECT_FLOAT_EQ(output.left, 1.25f);
        EXPECT_FLOAT_EQ(output.right, 1.25f);
    }

    TEST_F(ChorusTest, Calculate_smallDepthWithArithmeticAverage_correctSignal)
    {
        auto lfo = LFOMock();
        auto sut = Chorus();
        auto output = GetNanArray(13);
        auto input = GetInputArray(13);

        EXPECT_CALL(lfo, GetNextValue())
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0.5f))
            .WillOnce(testing::Return(1.0f))
            .WillOnce(testing::Return(0.5f))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(-0.5f))
            .WillOnce(testing::Return(-1.0f))
            .WillOnce(testing::Return(-0.5f))
            .WillOnce(testing::Return(0));

        StereoSample expected[] = {
            { input[0] +            0               },
            { input[1] +            0               },
            { input[2] +            0               },
            { input[3] +            0               },
            { input[4] +        input[1]            },
            { input[5] + (input[2] + input[3]) / 2  },
            { input[6] +        input[4]            },
            { input[7] + (input[4] + input[5]) / 2  },
            { input[8] +        input[5]            },
            { input[9] + (input[5] + input[6]) / 2  },
            { input[10] +       input[6]            },
            { input[11] + (input[7] + input[8]) / 2 },
            { input[12] +       input[9]            }
        };
        sut.SetDelay(5);
        sut.SetAlpha(1.0f);
        sut.SetDepth(3.0f/5);

        for (size_t i = 0; i < 13; i++) {
            sut.AddToBuffor(input[i]);
            output[i] = sut.Calculate(input[i], lfo.GetNextValue());
        }

        for (size_t i = 0; i < 13; i++) {
            EXPECT_FLOAT_EQ(output[i].left, expected[i].left);
            EXPECT_FLOAT_EQ(output[i].right, expected[i].right);
        }
    }

    TEST_F(ChorusTest, Calculate_smallDepthWithWeightedAverage_correctSignal)
    {
        auto lfo = LFOMock();
        auto sut = Chorus();
        auto output = GetNanArray(13);
        auto input = GetInputArray(13);

        EXPECT_CALL(lfo, GetNextValue())
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0.25f))
            .WillOnce(testing::Return(1.0f))
            .WillOnce(testing::Return(0.25f))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(-0.25f))
            .WillOnce(testing::Return(-1.0f))
            .WillOnce(testing::Return(-0.25f))
            .WillOnce(testing::Return(0));

        StereoSample expected[] = {
            { input[0] +            0               },
            { input[1] +            0               },
            { input[2] +            0               },
            { input[3] +            0               },
            { input[4] +        input[1]            },
            { input[5] + 0.75f * input[2] + 0.25f * input[3] },
            { input[6] +        input[4]            },
            { input[7] + 0.75f * input[4] + 0.25f * input[5] },
            { input[8] +        input[5]            },
            { input[9] + 0.25f * input[5] + 0.75f * input[6] },
            { input[10] +       input[6]            },
            { input[11] + 0.25f * input[7] + 0.75f * input[8] },
            { input[12] +       input[9]            }
        };
        sut.SetDelay(5);
        sut.SetAlpha(1.0f);
        sut.SetDepth(3.0f/5);

        for (size_t i = 0; i < 13; i++) {
            sut.AddToBuffor(input[i]);
            output[i] = sut.Calculate(input[i], lfo.GetNextValue());
        }

        for (size_t i = 0; i < 13; i++) {
            EXPECT_FLOAT_EQ(output[i].left, expected[i].left);
            EXPECT_FLOAT_EQ(output[i].right, expected[i].right);
        }
    }

    TEST_F(ChorusTest, Calculate_biggerDepth_correctSignal)
    {
        auto lfo = LFOMock();
        auto sut = Chorus();
        auto output = GetNanArray(13);
        auto input = GetInputArray(13);

        EXPECT_CALL(lfo, GetNextValue())
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0.25f))
            .WillOnce(testing::Return(1.0f))
            .WillOnce(testing::Return(0.25f))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(-0.25f))
            .WillOnce(testing::Return(-1.0f))
            .WillOnce(testing::Return(-0.25f))
            .WillOnce(testing::Return(0));

        StereoSample expected[] = {
            { input[0] +            0               },
            { input[1] +            0               },
            { input[2] +            0               },
            { input[3] +            0               },
            { input[4] +        input[2]            },
            { input[5] + 0.5f * input[3] + 0.5f * input[4] },
            { input[6] +        input[6]            },
            { input[7] + 0.5f * input[5] + 0.5f * input[6] },
            { input[8] +        input[6]            },
            { input[9] + 0.5f * input[6] + 0.5f * input[7] },
            { input[10] +       input[6]            },
            { input[11] + 0.5f * input[8] + 0.5f * input[9] },
            { input[12] +       input[10]            }
        };
        sut.SetDelay(5);
        sut.SetAlpha(1.0f);
        sut.SetDepth(5.0f/5);

        for (size_t i = 0; i < 13; i++) {
            sut.AddToBuffor(input[i]);
            output[i] = sut.Calculate(input[i], lfo.GetNextValue());
        }

        for (size_t i = 0; i < 13; i++) {
            EXPECT_FLOAT_EQ(output[i].left, expected[i].left);
            EXPECT_FLOAT_EQ(output[i].right, expected[i].right);
        }
    }

    TEST_F(ChorusTest, Calculate_alpha_correctSignal)
    {
        auto lfo = LFOMock();
        auto sut = Chorus();
        auto output = GetNanArray(13);
        auto input = GetInputArray(13);
        auto alpha = 0.5f;

        EXPECT_CALL(lfo, GetNextValue())
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(0.5f))
            .WillOnce(testing::Return(1.0f))
            .WillOnce(testing::Return(0.5f))
            .WillOnce(testing::Return(0))
            .WillOnce(testing::Return(-0.5f))
            .WillOnce(testing::Return(-1.0f))
            .WillOnce(testing::Return(-0.5f))
            .WillOnce(testing::Return(0));

        StereoSample expected[] = {
            { input[0] +                    0                       },
            { input[1] +                    0                       },
            { input[2] +                    0                       },
            { input[3] +                    0                       },
            { input[4] +            alpha * input[1]                },
            { input[5] +  alpha * (0.5f*input[2] + 0.5f*input[3])   },
            { input[6] +            alpha *  input[4]               },
            { input[7] +  alpha * (0.5f*input[4] + 0.5f*input[5])   },
            { input[8] +            alpha * input[5]                },
            { input[9] +  alpha * (0.5f*input[5] + 0.5f*input[6])   },
            { input[10] +           alpha * input[6]                },
            { input[11] + alpha * (0.5f*input[7] + 0.5f*input[8])   },
            { input[12] +           alpha * input[9]                }
        };
        sut.SetDelay(5);
        sut.SetAlpha(alpha);
        sut.SetDepth(3.0f/5);

        for (size_t i = 0; i < 13; i++) {
            sut.AddToBuffor(input[i]);
            output[i] = sut.Calculate(input[i], lfo.GetNextValue());
        }

        for (size_t i = 0; i < 13; i++) {
            EXPECT_FLOAT_EQ(output[i].left, expected[i].left);
            EXPECT_FLOAT_EQ(output[i].right, expected[i].right);
        }
    }
} // namespace
