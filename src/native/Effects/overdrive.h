#pragma once

#include <memory>
#include <vector>

#include "../IEffect.h"
#include "OverdriveAlgorithms/IOverdriveAlgorithm.h"
#include "OverdriveAlgorithms/HardClipping.h"
#include "OverdriveAlgorithms/HyperbolicTangent.h"

class Overdrive : public IEffect {
public:
    Overdrive();
    Overdrive(Overdrive &&) = default;
    Overdrive(const Overdrive &) = default;
    Overdrive &operator=(Overdrive &&) = default;
    Overdrive &operator=(const Overdrive &) = default;
    ~Overdrive() = default;

    void SetOn(const bool value) override;
    void Calculate(StereoSample &output, const StereoSample &input) override;

    void SetAlgorithm(const int value);
    int GetAlgorithmsNo();
    std::string GetAlgorithmName(int id);

    // Sets properties in algorithms
    void SetMinMaxValue(const float minValue, const float maxValue);
    void SetGain(const float value);
private:
    std::vector<std::shared_ptr<IOverdriveAlgorithm>> algorithms;
    int currentAlgorithm = 0;

    bool isOn = false;
};


