#include "Delay.h"

namespace Delay
{
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
        SetPropertyInAlgorithmsCalculation(
                [](auto alg){ return alg->IsUsingDelay(); },
                [=](auto alg){ alg->SetDelay(value / 1000 * settings->GetCurrentSampleRate()); }
            );
        SetPropertyInVisualization(
                [](auto alg){ return alg->IsUsingDelay(); },
                [=](auto alg){ alg->SetDelay(value); }
            );
    }

    void Delay::SetAlpha(const float value)
    {
        SetPropertyInAlgorithms(
                [](auto alg){ return alg->IsUsingAlpha(); },
                [=](auto alg){ alg->SetAlpha(value); }
            );
    }

    void Delay::SetFeedback(const float value)
    {
        SetPropertyInAlgorithms(
                [](auto alg){ return alg->IsUsingFeedback(); },
                [=](auto alg){ alg->SetFeedback(value); }
            );
    }

    bool Delay::IsUsingDelay()
    {
        return this->algorithms[currentAlgorithm]->IsUsingDelay();
    }

    bool Delay::IsUsingAlpha()
    {
        return this->algorithms[currentAlgorithm]->IsUsingAlpha();
    }

    bool Delay::IsUsingFeedback()
    {
        return this->algorithms[currentAlgorithm]->IsUsingFeedback();
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


    void Delay::SetPropertyInVisualization(std::function<bool(std::shared_ptr<IAlgorithm>)> IsImplemeting, std::function<void(std::shared_ptr<IAlgorithm>)> SetProperty)
    {
        for(auto alg : algorithmsVisualisation)
        {
            if(IsImplemeting(alg))
            {
                SetProperty(alg);
            }
        }
    }

    void Delay::SetPropertyInAlgorithmsCalculation(std::function<bool(std::shared_ptr<IAlgorithm>)> IsImplemeting, std::function<void(std::shared_ptr<IAlgorithm>)> SetProperty)
    {
        for(auto alg : algorithms)
        {
            if(IsImplemeting(alg))
            {
                SetProperty(alg);
            }
        }
    }

    void Delay::SetPropertyInAlgorithms(std::function<bool(std::shared_ptr<IAlgorithm>)> IsImplemeting, std::function<void(std::shared_ptr<IAlgorithm>)> SetProperty)
    {
        SetPropertyInAlgorithmsCalculation(IsImplemeting, SetProperty);
        SetPropertyInVisualization(IsImplemeting, SetProperty);
    }
}
