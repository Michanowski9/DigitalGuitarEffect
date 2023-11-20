#pragma once

#include "../Settings.h"
#include <memory>

struct StereoSample{
    float left;
    float right;

    friend StereoSample operator+(StereoSample lhs, const StereoSample &rhs)
    {
        lhs.left += rhs.left;
        lhs.right += rhs.right;
        return lhs;
    }

    friend StereoSample operator*(StereoSample lhs, const float &rhs)
    {
        lhs.left *= rhs;
        lhs.right *= rhs;
        return lhs;
    }
};

inline bool operator==(const StereoSample& lhs, const StereoSample& rhs){
    return lhs.left == rhs.left && lhs.right == rhs.right;
}

class IEffect {
public:
    virtual void operator()(StereoSample &output, const StereoSample &input) = 0;
    virtual void CalculateForVisualization(StereoSample &output, const StereoSample &input) = 0;

    void SetSettings(std::shared_ptr<Settings> obj) { settings = obj; };
    void SetOn(const bool value) { isOn = value; }

protected:
    std::shared_ptr<Settings> settings;
    bool isOn = false;
};

