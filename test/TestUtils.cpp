#include "TestUtils.h"

::testing::AssertionResult ExpectStereoSampleEqual(
    const char* expectedExpr,
    const char* actualExpr,
    const StereoSample& expected,
    const StereoSample& actual)
{
    if (expected.left == actual.left && expected.right == actual.right)
    {
        return ::testing::AssertionSuccess();
    }
    else
    {
        return ::testing::AssertionFailure()
            << "Actual:\n"
            << "\t" << actualExpr << " = \t{ left: " << actual.left << ", right: " << actual.right << " }\n"
            << "Expected:\n"
            << "\t" << expectedExpr << " = \t{ left: " << expected.left << ", right: " << expected.right << " }";
    }
}

