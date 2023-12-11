#include "Overdrive.h"

namespace Overdrive
{
    void Overdrive::AddAlgorithm(std::shared_ptr<IAlgorithm> algorithm)
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

    void Overdrive::SetPropertyInAlgorithms(std::function<bool(std::shared_ptr<IAlgorithm>)> IsImplemeting, std::function<void(std::shared_ptr<IAlgorithm>)> SetProperty)
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

    void Overdrive::SetOffset(const float value)
    {
        SetPropertyInAlgorithms(
                [](auto alg){ return alg->IsUsingOffset(); },
                [=](auto alg){ alg->SetOffset(value); }
            );
    }


    bool Overdrive::IsUsingGain()
    {
        return this->algorithms[currentAlgorithm]->IsUsingGain();
    }
    bool Overdrive::IsUsingMinValue()
    {
        return this->algorithms[currentAlgorithm]->IsUsingMinValue();
    }
    bool Overdrive::IsUsingMaxValue()
    {
        return this->algorithms[currentAlgorithm]->IsUsingMaxValue();
    }
    bool Overdrive::IsUsingOffset()
    {
        return this->algorithms[currentAlgorithm]->IsUsingOffset();
    }
}
