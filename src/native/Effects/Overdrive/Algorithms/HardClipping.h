#pragma once

#include "IAlgorithm.h"

namespace Overdrive
{
    class HardClipping : public IAlgorithm
    {
    public:
        HardClipping() = default;
        ~HardClipping() = default;

        StereoSample Calculate(const StereoSample &input) override
        {
            StereoSample output;

            output = (input - this->offset) * this->gain + this->offset;

            auto calc = [](const auto obj, auto& output){
                output = std::max(std::min(output,obj->maxValue), obj->minValue);
            };

            calc(this, output.left);
            calc(this, output.right);
            return output;
        };

        std::string GetName() override{
            return "Hard Clipping";
        }


        void SetGain(const float value) override { gain = value; };
        bool IsUsingGain() override { return true; }

        void SetMaxValue(const float value) override { maxValue = value; };
        bool IsUsingMaxValue() override { return true; }

        void SetMinValue(const float value) override { minValue = value; };
        bool IsUsingMinValue() override { return true; }

        void SetOffset(const float value) override { offset = value; };
        bool IsUsingOffset() override { return true; }
    private:
        float offset = 0.0f;
        float gain = 1.0f;
        float maxValue = 1.0f;
        float minValue = -1.0f;
    };
}
