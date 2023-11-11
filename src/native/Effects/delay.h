#pragma once

#include <queue>

#include "../IEffect.h"

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
    void SetOn(const bool value) override;

    void Calculate(StereoSample &output, const StereoSample &input, std::queue<StereoSample> &buffor, const int &bufforMaxSize);
    void AddToBuffor(const StereoSample &input, std::queue<StereoSample> &buffor, const int &bufforMaxSize);
    void SetDelay(const int value);
    void SetAlpha(const float value);
private:
    std::queue<StereoSample> buffor;
    bool isOn = false;
    float alpha = 0.5f;
    int bufforMaxSize = 1;
};


