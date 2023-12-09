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
        this->algorithms[currentAlgorithm]->SetDelay(static_cast<float>(value) / 1000 * settings->GetCurrentSampleRate());
        this->algorithmsVisualisation[currentAlgorithm]->SetDelay(value);
    }

    void Modulation::SetAlpha(const float value)
    {
        this->algorithms[currentAlgorithm]->SetAlpha(value);
        this->algorithmsVisualisation[currentAlgorithm]->SetAlpha(value);
    }

    void Modulation::SetDepth(const float value)
    {
        this->algorithms[currentAlgorithm]->SetDepth(value);
        this->algorithmsVisualisation[currentAlgorithm]->SetDepth(value);
    }

    void Modulation::SetLFOFrequency(const float value)
    {
        this->lfos[currentLFO]->SetFrequency(value);
        this->lfosVisualisation[currentLFO]->SetFrequency(value);
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
}
