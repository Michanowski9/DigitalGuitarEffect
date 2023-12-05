#pragma once

#include <memory>
#include <queue>
#include <initializer_list>

#include "IEffect.h"
#include "DelayAlgorithms/IDelayAlgorithms.h"
#include "DelayAlgorithms/CombFilter.h"

class Delay : public IEffect {
public:
    using AlgorithmPack = std::pair<std::shared_ptr<IDelayAlgorithm>, std::shared_ptr<IDelayAlgorithm>>;
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

    void SetDelayInMilliseconds(const int value);
    void SetAlpha(const float value);

    void SetAlgorithm(const int value) override;
    int GetAlgorithmsNo() override;
    std::string GetAlgorithmName(int id) override;

private:
    int currentAlgorithm = 0;
    std::vector<std::shared_ptr<IDelayAlgorithm>> algorithms;
    std::vector<std::shared_ptr<IDelayAlgorithm>> algorithmsVisualisation;
};


