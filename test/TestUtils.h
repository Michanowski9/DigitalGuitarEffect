#pragma once

#include <gtest/gtest.h>
#include <Effects/IEffect.h>

#define EXPECT_STEREOSAMPLE_EQ(actual, expected) \
    EXPECT_PRED_FORMAT2(ExpectStereoSampleEqual, expected, actual)

::testing::AssertionResult ExpectStereoSampleEqual(
    const char* expectedExpr,
    const char* actualExpr,
    const StereoSample& expected,
    const StereoSample& actual);


