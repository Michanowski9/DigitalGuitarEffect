#pragma once

#include "IOverdriveAlgorithm.h"

class HardClipping : public IOverdriveAlgorithm
{
public:
    HardClipping() = default;
    ~HardClipping() = default;

    StereoSample Calculate(const StereoSample &input) override
    {
        StereoSample output;
        output = input * this->gain;

        auto calc = [](const auto obj, auto& output){
            if(output > obj->maxValue)
            {
                output = obj->maxValue;
            }
            else if(output < obj->minValue)
            {
                output = obj->minValue;
            }
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

private:
    float gain = 1.0f;
    float maxValue = 1.0f;
    float minValue = -1.0f;
};
