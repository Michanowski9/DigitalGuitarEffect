#pragma once

#include "../IEffect.h"
#include "Algorithms/IAlgorithm.h"

#include <functional>
#include <initializer_list>
#include <memory>
#include <queue>

namespace Delay
{
    class Delay : public IEffect {
    public:
        using AlgorithmPack = std::pair<std::shared_ptr<IAlgorithm>, std::shared_ptr<IAlgorithm>>;
        Delay(std::initializer_list<AlgorithmPack> algorithms)
        {
            for(auto& alg : algorithms)
            {
                this->algorithms.push_back(alg.first);
                this->algorithmsVisualisation.push_back(alg.second);
            }
        };
        Delay(Delay &&) = default;
        Delay(const Delay &) = default;
        Delay &operator=(Delay &&) = default;
        Delay &operator=(const Delay &) = default;
        ~Delay() = default;

        void operator()(StereoSample &output, const StereoSample &input) override;
        void CalculateForVisualization(StereoSample &output, const StereoSample &input) override;
        void ResetEffect() override;

        void SetDelayInMilliseconds(const int value);
        void SetAlpha(const float value);
        void SetFeedback(const float value);
        void SetLeftInputVolume(const float value);
        void SetRightInputVolume(const float value);
        void SetTaps(const float value);

        bool IsUsingDelay();
        bool IsUsingAlpha();
        bool IsUsingFeedback();
        bool IsUsingLeftInputVolume();
        bool IsUsingRightInputVolume();
        bool IsUsingTaps();


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
    };
}
