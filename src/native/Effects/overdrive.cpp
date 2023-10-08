#include "overdrive.h"

void Overdrive::Calculate(StereoSample &output, const StereoSample &input)
{
    if(isOn)
    {
        HardClipping(output, input);
    }
    else
    {
        output = {input.left, input.right};
    }
}

void Overdrive::HardClipping(StereoSample &output, const StereoSample &input)
{
    output.left = input.left * multiplier;
    if(output.left > maxValue)
    {
        output.left = maxValue;
    }
    else if(output.left < minValue)
    {
        output.left = minValue;
    }

    output.right = input.right * multiplier;
    if(output.right > maxValue)
    {
        output.right = maxValue;
    }
    else if(output.right < minValue)
    {
        output.right = minValue;
    }
}

void Overdrive::SetOn(const bool value)
{
    isOn = value;
}

void Overdrive::Fuzz(StereoSample &output, const StereoSample &input)
{
    auto fuzz = [](const float &in){
        auto temp_fuzz = [](const float &in){
            if(in < 0.0){
                auto temp = in + 1.0f;
                return temp * temp * temp - 1.0f;
            }
            else{
                auto temp = in - 1.0f;
                return temp * temp * temp + 1.0f;
            }
        };
        return temp_fuzz(temp_fuzz(temp_fuzz(temp_fuzz(in))));
    };

    output.left = fuzz(input.left);
    output.right = fuzz(input.right);
}
