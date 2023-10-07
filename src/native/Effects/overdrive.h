#pragma once

#include "../IEffect.h"

class Overdrive : public IEffect {
public:
    Overdrive() = default;
    Overdrive(Overdrive &&) = default;
    Overdrive(const Overdrive &) = default;
    Overdrive &operator=(Overdrive &&) = default;
    Overdrive &operator=(const Overdrive &) = default;
    ~Overdrive() = default;

    void Calculate(StereoSample &output, const StereoSample &input) override;
private:
    void HardClipping(StereoSample &output, const StereoSample &input);
    void Fuzz(StereoSample &output, const StereoSample &input);

    bool isOn = true;
    float multiplier = 5;
    float minValue = -1.0f;
    float maxValue = 1.0f;
};


