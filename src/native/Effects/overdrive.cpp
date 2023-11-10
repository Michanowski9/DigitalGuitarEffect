#include "overdrive.h"

Overdrive::Overdrive()
{
    algorithms.push_back(std::make_shared<HardClipping>());
    algorithms.push_back(std::make_shared<HyperbolicTangent>());
};

void Overdrive::SetOn(const bool value)
{
    this->isOn = value;
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
        if(auto gainAlg = dynamic_cast<IGain*>(alg.get()))
        {
            gainAlg->SetGain(value);
        }
    }
}

void Overdrive::SetMinMaxValue(const float minValue, const float maxValue)
{
    for(auto alg : algorithms)
    {
        if(auto gainAlg = dynamic_cast<IMinMaxValue*>(alg.get()))
        {
            gainAlg->SetMinValue(minValue);
            gainAlg->SetMaxValue(maxValue);
        }
    }
}
