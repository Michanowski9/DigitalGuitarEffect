#pragma once

#include "../IEffect.h"
#include "Algorithms/IAlgorithm.h"
#include "LFO/ILFO.h"

#include <functional>
#include <initializer_list>
#include <memory>
#include <queue>

namespace Modulation
{
    class Modulation : public IEffect {
    public:
        using AlgorithmPack = std::pair<std::shared_ptr<IAlgorithm>, std::shared_ptr<IAlgorithm>>;
        using LFOPack = std::pair<std::shared_ptr<ILFO>, std::shared_ptr<ILFO>>;

        Modulation(std::initializer_list<AlgorithmPack> algorithms, std::initializer_list<LFOPack> lfos);
        Modulation(Modulation &&) = default;
        Modulation(const Modulation &) = default;
        Modulation &operator=(Modulation &&) = default;
        Modulation &operator=(const Modulation &) = default;
        ~Modulation() = default;

        void operator()(StereoSample &output, const StereoSample &input) override;
        void CalculateForVisualization(StereoSample &output, const StereoSample &input) override;
        void ResetEffect() override;

        void SetDelayInMilliseconds(const int value);
        void SetAlpha(const float value);
        void SetFeedback(const float value);
        void SetDepth(const float value);
        void SetLFOFrequency(const float value);

        bool IsUsingDelay();
        bool IsUsingAlpha();
        bool IsUsingFeedback();
        bool IsUsingDepth();
        bool IsUsingLFOFrequency();

        int GetLFOsNo();
        std::string GetLFOName(int id);
        void SetLFO(const int value);

        void SetAlgorithm(const int value) override;
        int GetAlgorithmsNo() override;
        std::string GetAlgorithmName(int id) override;

    private:
        void SetPropertyInAlgorithms(std::function<bool(std::shared_ptr<IAlgorithm>)> IsImplemeting, std::function<void(std::shared_ptr<IAlgorithm>)> SetProperty);
        void SetPropertyInVisualization(std::function<bool(std::shared_ptr<IAlgorithm>)> IsImplemeting, std::function<void(std::shared_ptr<IAlgorithm>)> SetProperty);
        void SetPropertyInAlgorithmsCalculation(std::function<bool(std::shared_ptr<IAlgorithm>)> IsImplemeting, std::function<void(std::shared_ptr<IAlgorithm>)> SetProperty);

        int currentAlgorithm = 0;
        std::vector<std::shared_ptr<IAlgorithm>> algorithms;
        std::vector<std::shared_ptr<IAlgorithm>> algorithmsVisualisation;

        int currentLFO = 0;
        std::vector<std::shared_ptr<ILFO>> lfos;
        std::vector<std::shared_ptr<ILFO>> lfosVisualisation;
    };
}
