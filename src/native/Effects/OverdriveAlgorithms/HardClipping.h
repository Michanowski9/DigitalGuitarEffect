#pragma once

#include "IOverdriveAlgorithm.h"
#include "IGain.h"
#include "IMinMaxValue.h"

class HardClipping : public IOverdriveAlgorithm, public IGain, public IMinMaxValue
{
public:
    HardClipping() = default;
    ~HardClipping() = default;

    void operator()(StereoSample &output, const StereoSample &input) override
    {
        auto calc = [](const auto obj, auto& output, auto& input) {
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
};
