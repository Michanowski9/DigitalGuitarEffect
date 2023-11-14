#pragma once

#include <memory>
#include <vector>

#include "IEffect.h"
#include "OverdriveAlgorithms/IOverdriveAlgorithm.h"
#include "OverdriveAlgorithms/HardClipping.h"
#include "OverdriveAlgorithms/HyperbolicTangent.h"


class Overdrive : public IEffect {
public:
    using AlgorithmsContainer = std::vector<std::shared_ptr<IOverdriveAlgorithm>>;

    Overdrive() = default;
    Overdrive(Overdrive &&) = default;
    Overdrive(const Overdrive &) = default;
    Overdrive &operator=(Overdrive &&) = default;
    Overdrive &operator=(const Overdrive &) = default;
    ~Overdrive() = default;

    void operator()(StereoSample &output, const StereoSample &input) override;
    void CalculateForVisualization(StereoSample &output, const StereoSample &input) override;

    void SetAlgorithms(AlgorithmsContainer algorithmsContainer);

    void SetAlgorithm(const int value);
    int GetAlgorithmsNo();
    std::string GetAlgorithmName(int id);

    void SetMinMaxValue(const float minValue, const float maxValue);
    void SetGain(const float value);

private:
    void Calculate(StereoSample &output, const StereoSample &input);

    AlgorithmsContainer algorithms;
    int currentAlgorithm = 0;
};


