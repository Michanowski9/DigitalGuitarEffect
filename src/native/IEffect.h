#pragma once

struct StereoSample{
    float left;
    float right;
};

class IEffect {
public:
    virtual void operator()(StereoSample &output, const StereoSample &input) = 0;
    virtual void SetOn(const bool value) = 0;
    virtual void CalculateForVisualization(StereoSample &output, const StereoSample &input) = 0;
};

