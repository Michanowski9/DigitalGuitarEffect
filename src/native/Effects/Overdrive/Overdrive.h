#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "../IEffect.h"
#include "Algorithms/IAlgorithm.h"

namespace Overdrive
{
    class Overdrive : public IEffect {
    public:
        using AlgorithmsContainer = std::vector<std::shared_ptr<IAlgorithm>>;

        Overdrive() = default;
        Overdrive(Overdrive &&) = default;
        Overdrive(const Overdrive &) = default;
        Overdrive &operator=(Overdrive &&) = default;
        Overdrive &operator=(const Overdrive &) = default;
        ~Overdrive() = default;

        void operator()(StereoSample &output, const StereoSample &input) override;
        void CalculateForVisualization(StereoSample &output, const StereoSample &input) override;

        void AddAlgorithm(std::shared_ptr<IAlgorithm> algorithm);

        void SetAlgorithm(const int value) override;
        int GetAlgorithmsNo() override;
        std::string GetAlgorithmName(int id) override;

        void SetMinValue(const float value);
        bool IsUsingMinValue();

        void SetMaxValue(const float value);
        bool IsUsingMaxValue();

        void SetGain(const float value);
        bool IsUsingGain();

    private:
        void Calculate(StereoSample &output, const StereoSample &input);
        void SetPropertyInAlgorithms(std::function<bool(std::shared_ptr<IAlgorithm>)> IsImplemeting, std::function<void(std::shared_ptr<IAlgorithm>)> SetProperty);

        AlgorithmsContainer algorithms;
        int currentAlgorithm = 0;
    };
}
