#pragma once

#include "../Settings.h"
#include "../StereoSample.h"

#include <memory>
#include <string>

class IEffect {
public:
    virtual void operator()(StereoSample &output, const StereoSample &input) = 0;
    virtual void CalculateForVisualization(StereoSample &output, const StereoSample &input) = 0;

    virtual std::string GetAlgorithmName(int id) { return "no algorithms"; }
    virtual int GetAlgorithmsNo() { return 0; }
    virtual void SetAlgorithm(const int value) { }

    virtual void ResetEffect() { }
    void SetSettings(std::shared_ptr<Settings> obj) { settings = obj; };
    void SetOn(const bool value) { isOn = value; }
protected:
    std::shared_ptr<Settings> settings;
    bool isOn = false;
};

