#pragma once

#include <gtest/gtest.h>
#include <Effects/IEffect.h>

inline bool operator==(const StereoSample& lhs, const StereoSample& rhs)
{
    return lhs.left == rhs.left && lhs.right == rhs.right;
}

inline std::ostream& operator<<(std::ostream& os, const StereoSample& arg)
{
    return os << "{ " << arg.left << ", " << arg.right << " }";
}

/*inline StereoSample operator*(StereoSample lhs, const float &rhs)
{
    lhs.left *= rhs;
    lhs.right *= rhs;
    return lhs;
}

inline StereoSample operator+(StereoSample lhs, const StereoSample &rhs)
{
    lhs.left += rhs.left;
    lhs.right += rhs.right;
    return lhs;
}*/
