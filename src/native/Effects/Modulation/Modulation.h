#pragma once

#include <memory>
#include <queue>
#include <initializer_list>

#include "../IEffect.h"
#include "Algorithms/IAlgorithm.h"
#include "LFO/ILFO.h"

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
    void SetDepth(const float value);
    void SetLFOFrequency(const float value);

    void SetAlgorithm(const int value) override;
    int GetAlgorithmsNo() override;
    std::string GetAlgorithmName(int id) override;

private:
    int currentAlgorithm = 0;
    std::vector<std::shared_ptr<IAlgorithm>> algorithms;
    std::vector<std::shared_ptr<IAlgorithm>> algorithmsVisualisation;

    int currentLFO = 0;
    std::vector<std::shared_ptr<ILFO>> lfos;
    std::vector<std::shared_ptr<ILFO>> lfosVisualisation;
};


