#pragma once

#include "../Settings.h"
#include <memory>

struct StereoSample{
    float left;
    float right;
};

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

