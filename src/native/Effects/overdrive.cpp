#include "overdrive.h"

void Overdrive::SetAlgorithms(AlgorithmsContainer algorithmsContainer)
{
    for(auto algorithm : algorithmsContainer)
    {
        algorithms.push_back(algorithm);
    }
}

void Overdrive::operator()(StereoSample &output, const StereoSample &input)
{
    if(isOn)
    {
        Calculate(output, input);
    }
    else
    {
        output = {input.left, input.right};
    }
}

void Overdrive::CalculateForVisualization(StereoSample &output, const StereoSample &input){
    Calculate(output, input);
}

void Overdrive::Calculate(StereoSample &output, const StereoSample &input){
    (*this->algorithms[this->currentAlgorithm])(output, input);
}

void Overdrive::SetAlgorithm(const int value)
{
    this->currentAlgorithm = value;
}

int Overdrive::GetAlgorithmsNo()
{
    return this->algorithms.size();
}

std::string Overdrive::GetAlgorithmName(int id)
{
    return this->algorithms[id]->GetName();
}

void Overdrive::SetGain(const float value)
{
    for(auto alg : algorithms)
    {
        if(alg->IsUsingGain())
        {
            alg->SetGain(value);
        }
    }
}

void Overdrive::SetMinMaxValue(const float minValue, const float maxValue)
{
    for(auto alg : algorithms)
    {
        if(alg->IsUsingMinValue())
        {
            alg->SetMinValue(minValue);
        }
        if(alg->IsUsingMaxValue())
        {
            alg->SetMaxValue(maxValue);
        }
    }
}
