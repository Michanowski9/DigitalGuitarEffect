#include "TestUtils.h"

std::vector<StereoSample> GetNanArray(size_t size){
    std::vector<StereoSample> result;
    for (size_t i = 0; i < size; i++) {
        result.push_back({ std::nanf(" "), std::nanf(" ") });
    }
    return result;
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

