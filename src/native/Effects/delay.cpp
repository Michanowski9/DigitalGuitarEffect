#include "delay.h"

void Delay::operator()(StereoSample &output, const StereoSample &input)
{
    if(isOn)
    {
        output = algorithm->Calculate(input);
    }
    else
    {
        output = input;
    }
    algorithm->AddToBuffor(input);
}

void Delay::CalculateForVisualization(StereoSample &output, const StereoSample &input)
{
    output = this->algorithmVisualisation->Calculate(input);
    this->algorithmVisualisation->AddToBuffor(input);
}

void Delay::SetDelayInMilliseconds(const int value)
{
    this->algorithm->SetDelay(static_cast<float>(value) / 1000 * settings->GetCurrentSampleRate());
    this->algorithmVisualisation->SetDelay(value);
}

void Delay::SetAlpha(const float value)
{
    this->algorithm->SetAlpha(value);
    this->algorithmVisualisation->SetAlpha(value);
}
