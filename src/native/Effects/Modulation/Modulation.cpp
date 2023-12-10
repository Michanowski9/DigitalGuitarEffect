#include "Modulation.h"

namespace Modulation
{
    Modulation::Modulation(std::initializer_list<AlgorithmPack> algorithms, std::initializer_list<LFOPack> lfos)
    {
        for(auto& alg : algorithms)
        {
            this->algorithms.push_back(alg.first);
            this->algorithmsVisualisation.push_back(alg.second);
        }
        for(auto& lfo : lfos)
        {
            this->lfos.push_back(lfo.first);
            this->lfosVisualisation.push_back(lfo.second);
        }
    };

    void Modulation::operator()(StereoSample &output, const StereoSample &input)
    {
        if(isOn)
        {
            auto lfoValue = lfos[currentLFO]->GetNextValue();
            output = algorithms[currentAlgorithm]->Calculate(input, lfoValue);
        }
        else
        {
            output = input;
        }
        algorithms[currentAlgorithm]->AddToBuffor(input);
    }

    void Modulation::ResetEffect()
    {
        lfosVisualisation[currentLFO]->ResetCounter();
        algorithmsVisualisation[currentAlgorithm]->ResetBuffor();
    }

    void Modulation::CalculateForVisualization(StereoSample &output, const StereoSample &input)
    {
        auto lfoValue = lfosVisualisation[currentLFO]->GetNextValue();
        output = this->algorithmsVisualisation[currentAlgorithm]->Calculate(input, lfoValue);
        this->algorithmsVisualisation[currentAlgorithm]->AddToBuffor(input);
    }


    void Modulation::SetDelayInMilliseconds(const int value)
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

    void Modulation::SetAlpha(const float value)
    {
        SetPropertyInAlgorithms(
                [](auto alg){ return alg->IsUsingAlpha(); },
                [=](auto alg){ alg->SetAlpha(value); }
            );
    }

    void Modulation::SetFeedback(const float value)
    {
        SetPropertyInAlgorithms(
                [](auto alg){ return alg->IsUsingFeedback(); },
                [=](auto alg){ alg->SetFeedback(value); }
            );
    }

    void Modulation::SetDepth(const float value)
    {
        SetPropertyInAlgorithms(
                [](auto alg){ return alg->IsUsingDepth(); },
                [=](auto alg){ alg->SetDepth(value); }
            );
    }

    void Modulation::SetLFOFrequency(const float value)
    {
        this->lfos[currentLFO]->SetFrequency(value);
        this->lfosVisualisation[currentLFO]->SetFrequency(value);
    }

    bool Modulation::IsUsingDelay()
    {
        return this->algorithms[currentAlgorithm]->IsUsingDelay();
    }
    bool Modulation::IsUsingAlpha()
    {
        return this->algorithms[currentAlgorithm]->IsUsingAlpha();
    }
    bool Modulation::IsUsingFeedback()
    {
        return this->algorithms[currentAlgorithm]->IsUsingFeedback();
    }
    bool Modulation::IsUsingDepth()
    {
        return this->algorithms[currentAlgorithm]->IsUsingDepth();
    }
    bool Modulation::IsUsingLFOFrequency()
    {
        return this->lfos[currentLFO]->IsUsingFrequency();
    }

    int Modulation::GetLFOsNo()
    {
        return this->lfos.size();
    }

    std::string Modulation::GetLFOName(int id)
    {
        return this->lfos[id]->GetName();
    }

    void Modulation::SetLFO(const int value)
    {
        this->currentLFO = value;
    }

    void Modulation::SetAlgorithm(const int value)
    {
        this->currentAlgorithm = value;
    }

    int Modulation::GetAlgorithmsNo()
    {
        return this->algorithms.size();
    }

    std::string Modulation::GetAlgorithmName(int id)
    {
        return this->algorithms[id]->GetName();
    }


    void Modulation::SetPropertyInVisualization(std::function<bool(std::shared_ptr<IAlgorithm>)> IsImplemeting, std::function<void(std::shared_ptr<IAlgorithm>)> SetProperty)
    {
        for(auto alg : algorithmsVisualisation)
        {
            if(IsImplemeting(alg))
            {
                SetProperty(alg);
            }
        }
    }

    void Modulation::SetPropertyInAlgorithmsCalculation(std::function<bool(std::shared_ptr<IAlgorithm>)> IsImplemeting, std::function<void(std::shared_ptr<IAlgorithm>)> SetProperty)
    {
        for(auto alg : algorithms)
        {
            if(IsImplemeting(alg))
            {
                SetProperty(alg);
            }
        }
    }

    void Modulation::SetPropertyInAlgorithms(std::function<bool(std::shared_ptr<IAlgorithm>)> IsImplemeting, std::function<void(std::shared_ptr<IAlgorithm>)> SetProperty)
    {
        SetPropertyInAlgorithmsCalculation(IsImplemeting, SetProperty);
        SetPropertyInVisualization(IsImplemeting, SetProperty);
    }
}

