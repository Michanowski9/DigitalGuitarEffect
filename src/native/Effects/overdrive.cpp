#include "overdrive.h"
#include <memory>

void Overdrive::AddAlgorithm(std::shared_ptr<IOverdriveAlgorithm> algorithm)
{
    algorithms.push_back(algorithm);
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
    output = this->algorithms[this->currentAlgorithm]->Calculate(input);
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

void Overdrive::SetPropertyInAlgorithms(std::function<bool(std::shared_ptr<IOverdriveAlgorithm>)> IsImplemeting, std::function<void(std::shared_ptr<IOverdriveAlgorithm>)> SetProperty)
{
    for(auto alg : algorithms)
    {
        if(IsImplemeting(alg))
        {
            SetProperty(alg);
        }
    }
}

void Overdrive::SetGain(const float value)
{
    SetPropertyInAlgorithms(
            [](auto alg){ return alg->IsUsingGain(); },
            [=](auto alg){ alg->SetGain(value); }
        );
}

void Overdrive::SetMinValue(const float value)
{
    SetPropertyInAlgorithms(
            [](auto alg){ return alg->IsUsingMinValue(); },
            [=](auto alg){ alg->SetMinValue(value); }
        );
}

void Overdrive::SetMaxValue(const float value)
{
    SetPropertyInAlgorithms(
            [](auto alg){ return alg->IsUsingMaxValue(); },
            [=](auto alg){ alg->SetMaxValue(value); }
        );
}
