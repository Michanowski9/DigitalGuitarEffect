#include "delay.h"

void Delay::operator()(StereoSample &output, const StereoSample &input)
{
    if(isOn)
    {
        output = algorithms[currentAlgorithm]->Calculate(input);
    }
    else
    {
        output = input;
    }
    algorithms[currentAlgorithm]->AddToBuffor(input);
}

void Delay::CalculateForVisualization(StereoSample &output, const StereoSample &input)
{
    output = this->algorithmsVisualisation[currentAlgorithm]->Calculate(input);
    this->algorithmsVisualisation[currentAlgorithm]->AddToBuffor(input);
}

void Delay::SetDelayInMilliseconds(const int value)
{
    this->algorithms[currentAlgorithm]->SetDelay(static_cast<float>(value) / 1000 * settings->GetCurrentSampleRate());
    this->algorithmsVisualisation[currentAlgorithm]->SetDelay(value);
}

void Delay::SetAlpha(const float value)
{
    this->algorithms[currentAlgorithm]->SetAlpha(value);
    this->algorithmsVisualisation[currentAlgorithm]->SetAlpha(value);
}

void Delay::SetAlgorithm(const int value)
{
    this->currentAlgorithm = value;
}

int Delay::GetAlgorithmsNo()
{
    return this->algorithms.size();
}

std::string Delay::GetAlgorithmName(int id)
{
    return this->algorithms[id]->GetName();
}

