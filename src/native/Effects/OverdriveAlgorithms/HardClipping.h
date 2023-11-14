#pragma once

#include "IOverdriveAlgorithm.h"

class HardClipping : public IOverdriveAlgorithm
{
public:
    HardClipping() = default;
    ~HardClipping() = default;

    void operator()(StereoSample &output, const StereoSample &input) override
    {
        auto calc = [](const auto obj, auto& output, auto& input){
            output = input * obj->gain;
            if(output > obj->maxValue)
            {
                output = obj->maxValue;
            }
            else if(output < obj->minValue)
            {
                output = obj->minValue;
            }
        };

        calc(this, output.left, input.left);
        calc(this, output.right, input.right);
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

private:
    float gain = 1.0f;
    float maxValue = 1.0f;
    float minValue = -1.0f;
};
