#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Effects/IEffect.h>
#include <math.h>

inline bool operator==(const StereoSample& lhs, const StereoSample& rhs)
{
    return lhs.left == rhs.left && lhs.right == rhs.right;
}

inline std::ostream& operator<<(std::ostream& os, const StereoSample& arg)
{
    return os << "{ " << arg.left << ", " << arg.right << " }";
}

std::vector<StereoSample> GetNanArray(size_t size);
std::vector<StereoSample> GetInputArray(size_t size);

inline StereoSample operator+(StereoSample lhs, const float &rhs)
{
    lhs.left += rhs;
    lhs.right += rhs;
    return lhs;
}
