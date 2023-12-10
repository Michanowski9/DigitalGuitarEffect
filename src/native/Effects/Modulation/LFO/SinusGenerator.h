#pragma once

#include "../../../Settings.h"
#include "ILFO.h"

#include <cmath>
#include <memory>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

namespace Modulation {
    class SinusGenerator : public ILFO {
    public:
        SinusGenerator(std::shared_ptr<Settings> settings)
            :settings(settings)
        {

        };
        SinusGenerator(SinusGenerator &&) = default;
        SinusGenerator(const SinusGenerator &) = default;
        SinusGenerator &operator=(SinusGenerator &&) = default;
        SinusGenerator &operator=(const SinusGenerator &) = default;
        ~SinusGenerator() = default;

        void SetFrequency(const float value) override
        {
            frequency = value;
        }

        bool IsUsingFrequency() override { return true; }

        void ResetCounter() override {
            counter = 0;
        }

        float GetNextValue() override {
            auto t = static_cast<float>(counter) / settings->GetCurrentSampleRate();
            auto result = std::sin(2 * M_PI * frequency * t);
            counter++;
            return result;
        }

        std::string GetName() override { return "Sinus"; }
    private:
        float frequency = 1.0f;
        int counter = 0;
        std::shared_ptr<Settings> settings;

    };
}
