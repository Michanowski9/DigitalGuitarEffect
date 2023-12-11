#pragma once

struct StereoSample{
    float left;
    float right;
};

inline StereoSample operator*(const float& lhs, StereoSample rhs)
{
    rhs.left *= lhs;
    rhs.right *= lhs;
    return rhs;
}

inline StereoSample operator*(StereoSample lhs, const float &rhs)
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
}

inline StereoSample operator/(StereoSample lhs, const float &rhs)
{
    lhs.left /= rhs;
    lhs.right /= rhs;
    return lhs;
}

inline StereoSample operator-(StereoSample lhs, const StereoSample &rhs)
{
    lhs.left -= rhs.left;
    lhs.right -= rhs.right;
    return lhs;
}

inline StereoSample operator+(StereoSample lhs, const float &rhs)
{
    lhs.left += rhs;
    lhs.right += rhs;
    return lhs;
}

inline StereoSample operator-(StereoSample lhs, const float &rhs)
{
    lhs.left -= rhs;
    lhs.right -= rhs;
    return lhs;
}
