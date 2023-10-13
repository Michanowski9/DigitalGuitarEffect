#include "overdrive.h"

void Overdrive::Calculate(StereoSample &output, const StereoSample &input)
{
    if(isOn)
    {
        //TODO: remove this switch and use i.e. array, vector. Not use enum
        switch(algorithm)
        {
            case Algorithm::HardClipping:
                HardClipping(output, input);
                break;
            case Algorithm::SoftClipping:
                SoftClipping(output, input);
                break;
            case Algorithm::Fuzz:
                Fuzz(output, input);
                break;
            case Algorithm::HyperbolicTangent:
                HyperbolicTangent(output, input);
                break;
            default:
                output = {input.left, input.right};
                break;
        }
    }
    else
    {
        output = {input.left, input.right};
    }
}

// TODO: algorithms should be in another classes
void Overdrive::HardClipping(StereoSample &output, const StereoSample &input)
{
    output.left = input.left * gain;
    if(output.left > maxValue)
    {
        output.left = maxValue;
    }
    else if(output.left < minValue)
    {
        output.left = minValue;
    }

    output.right = input.right * gain;
    if(output.right > maxValue)
    {
        output.right = maxValue;
    }
    else if(output.right < minValue)
    {
        output.right = minValue;
    }
}

// TODO: correct algorithm
void Overdrive::SoftClipping(StereoSample &output, const StereoSample &input)
{
    output.left = input.left * gain;
    if(output.left > maxValue)
    {
        output.left = maxValue + (output.left - maxValue) * softCut;
    }
    else if(output.left < minValue)
    {
        output.left = minValue + (output.left + maxValue) * softCut;
    }

    output.right = input.right * gain;
    if(output.right > maxValue)
    {
        output.right = maxValue + (output.right - maxValue) * softCut;
    }
    else if(output.right < minValue)
    {
        output.right = minValue + (output.right + maxValue) * softCut;
    }
}

// TODO: correct algorithm
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
//        return temp_fuzz(temp_fuzz(temp_fuzz(temp_fuzz(in))));
        return temp_fuzz(in);
    };

    output.left = fuzz(input.left);
    output.right = fuzz(input.right);
}

void Overdrive::HyperbolicTangent(StereoSample &output, const StereoSample &input)
{
    if (gain == 0)
    {
        output = { .left=0.0f, .right=0.0f };
        return;
    }
    output.left = std::tanh(gain * (input.left >= 0 ? maxValue : -minValue) * input.left) / std::tanh(gain);
    output.right = std::tanh(gain * (input.right >= 0 ? maxValue : -minValue) * input.right) / std::tanh(gain);
}

void Overdrive::SetOn(const bool value)
{
    this->isOn = value;
}

void Overdrive::SetGain(const float value)
{
    this->gain = value;
}

// TODO: this should be two functions
void Overdrive::SetMinValue(const float value)
{
    this->minValue = value;
}

void Overdrive::SetMaxValue(const float value)
{
    this->maxValue = value;
}

void Overdrive::SetSoftCutValue(const float value)
{
    this->softCut = value;
}

void Overdrive::SetAlgorithm(const Algorithm algorithm)
{
    this->algorithm = algorithm;
}
