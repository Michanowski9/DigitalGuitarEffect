#pragma once

#include <memory>
#include <vector>
#include <functional>

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

    void AddAlgorithm(std::shared_ptr<IOverdriveAlgorithm> algorithm);

    void SetAlgorithm(const int value);
    int GetAlgorithmsNo();
    std::string GetAlgorithmName(int id);

    void SetMinValue(const float value);
    void SetMaxValue(const float value);
    void SetGain(const float value);

private:
    void Calculate(StereoSample &output, const StereoSample &input);
    void SetPropertyInAlgorithms(std::function<bool(std::shared_ptr<IOverdriveAlgorithm>)> IsImplemeting, std::function<void(std::shared_ptr<IOverdriveAlgorithm>)> SetProperty);

    AlgorithmsContainer algorithms;
    int currentAlgorithm = 0;
};


