#pragma once

#include <memory>
#include <queue>

#include "IEffect.h"
#include "DelayAlgorithms/IDelayAlgorithms.h"
#include "DelayAlgorithms/CombFilter.h"

class Delay : public IEffect {
public:
    Delay(){
        algorithm = std::make_shared<CombFilter>();
        algorithmVisualisation = std::make_shared<CombFilter>();
    };
    Delay(Delay &&) = default;
    Delay(const Delay &) = default;
    Delay &operator=(Delay &&) = default;
    Delay &operator=(const Delay &) = default;
    ~Delay() = default;

    void operator()(StereoSample &output, const StereoSample &input) override;
    void CalculateForVisualization(StereoSample &output, const StereoSample &input) override;

    void SetDelayInMilliseconds(const int value);
    void SetAlpha(const float value);

private:
    std::shared_ptr<IDelayAlgorithm> algorithm;
    std::shared_ptr<IDelayAlgorithm> algorithmVisualisation;
};


