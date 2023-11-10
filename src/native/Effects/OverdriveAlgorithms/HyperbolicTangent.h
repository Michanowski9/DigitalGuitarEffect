#pragma once

#include "IOverdriveAlgorithm.h"
#include "IGain.h"
#include "IMinMaxValue.h"

#include <cmath>

class HyperbolicTangent : public IOverdriveAlgorithm, public IGain, public IMinMaxValue
{
public:
    HyperbolicTangent() = default;
    ~HyperbolicTangent() = default;

    void operator()(StereoSample &output, const StereoSample &input) override
    {
        auto calc = [](const auto obj, auto& output, auto& input) {
            if (obj->gain == 0)
            {
                output = 0.0f;
                return;
            }
            output = std::tanh(obj->gain * input) / std::tanh(obj->gain) * (input >= 0 ? obj->maxValue : -(obj->minValue));
        };

        calc(this, output.left, input.left);
        calc(this, output.right, input.right);
    }

    std::string GetName() override {
        return "Hyperbolic Tangent";
    };
};
