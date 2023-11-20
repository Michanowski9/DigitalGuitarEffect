#pragma once

#include "IOverdriveAlgorithm.h"

#include <cmath>

class HyperbolicTangent : public IOverdriveAlgorithm
{
public:
    HyperbolicTangent() = default;
    ~HyperbolicTangent() = default;

    StereoSample Calculate(const StereoSample &input) override
    {
        StereoSample output;
        auto calc = [](const auto obj, auto& output, auto& input) {
            if(obj->gain == 0)
            {
                output = 0;
                return;
            }
            output = std::tanh(obj->gain * input) / std::tanh(obj->gain);
            output *= (input >= 0 ? obj->maxValue : -obj->minValue);
        };

        calc(this, output.left, input.left);
        calc(this, output.right, input.right);
        return output;
    }

    std::string GetName() override {
        return "Hyperbolic Tangent";
    };


    void SetGain(const float value) override { gain = value; };
    bool IsUsingGain() override { return true; }

    void SetMaxValue(const float value) override { maxValue = value; };
    bool IsUsingMaxValue() override { return true; }

    void SetMinValue(const float value) override { minValue = value; };
    bool IsUsingMinValue() override { return true; }

private:
    float gain = 1.0f;
    float maxValue = 1.0f;
    float minValue = -1.0f;
};
