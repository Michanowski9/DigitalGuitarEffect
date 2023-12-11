#pragma once

#include "IAlgorithm.h"

#include <cmath>

namespace Overdrive
{
    class Exponential : public IAlgorithm
    {
    public:
        Exponential() = default;
        ~Exponential() = default;

        StereoSample Calculate(const StereoSample &input) override
        {
            StereoSample output;
            auto calc = [](const auto obj, auto& output, auto& input) {
                if(obj->gain == 0)
                {
                    output = 0;
                    return;
                }
                output = ((2.0 / (1.0 + std::exp(-input * obj->gain))) - 1.0) / (2.0 / ((1.0 + std::exp(-obj->gain)))-1.0);
                output *= (input >= 0 ? obj->maxValue : -obj->minValue);
            };

            calc(this, output.left, input.left);
            calc(this, output.right, input.right);
            return output;
        }

        std::string GetName() override {
            return "Exponential";
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
}
