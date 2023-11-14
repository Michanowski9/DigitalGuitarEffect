#pragma once

#include <memory>
#include <queue>

#include "IEffect.h"

class Delay : public IEffect {
public:
    Delay() = default;
    Delay(Delay &&) = default;
    Delay(const Delay &) = default;
    Delay &operator=(Delay &&) = default;
    Delay &operator=(const Delay &) = default;
    ~Delay() = default;

    void operator()(StereoSample &output, const StereoSample &input) override;
    void CalculateForVisualization(StereoSample &output, const StereoSample &input) override;

    void SetDelay(const int value);
    void SetAlpha(const float value);

private:
    void Calculate(StereoSample &output, const StereoSample &input, std::queue<StereoSample> &buffor, const int &bufforMaxSize);
    void AddToBuffor(const StereoSample &input, std::queue<StereoSample> &buffor, const int &bufforMaxSize);

    std::queue<StereoSample> buffor;
    float alpha = 0.5f;
    int bufforMaxSize = 1;
};


