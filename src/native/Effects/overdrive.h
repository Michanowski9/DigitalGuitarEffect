#pragma once

#include <cmath>
#include "../IEffect.h"

class Overdrive : public IEffect {
public:
    enum class Algorithm {
        HardClipping,
        SoftClipping,
        Fuzz,
        SavShape,
        HyperbolicTangent
    };
    Overdrive() = default;
    Overdrive(Overdrive &&) = default;
    Overdrive(const Overdrive &) = default;
    Overdrive &operator=(Overdrive &&) = default;
    Overdrive &operator=(const Overdrive &) = default;
    ~Overdrive() = default;

    void Calculate(StereoSample &output, const StereoSample &input) override;
    void SetOn(const bool value) override;

    void SetGain(const float value);
    void SetMinValue(const float value);
    void SetMaxValue(const float value);
    void SetSoftCutValue(const float value);
    void SetAlgorithm(const Algorithm algorithm);
private:
    void HardClipping(StereoSample &output, const StereoSample &input);
    void SoftClipping(StereoSample &output, const StereoSample &input);
    void HyperbolicTangent(StereoSample &output, const StereoSample &input);
    void Fuzz(StereoSample &output, const StereoSample &input);

    Algorithm algorithm = Algorithm::SoftClipping;
    bool isOn = false;
    float gain = 1;
    float softCut = 0.0f;
    float minValue = -1.0f;
    float maxValue = 1.0f;
};


