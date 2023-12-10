#pragma once

#include "../../../Settings.h"
#include "ILFO.h"

#include <cmath>
#include <memory>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

namespace Modulation {
    class SquareGenerator : public ILFO {
    public:
        SquareGenerator(std::shared_ptr<Settings> settings)
            :settings(settings)
        {

        };
        SquareGenerator(SquareGenerator &&) = default;
        SquareGenerator(const SquareGenerator &) = default;
        SquareGenerator &operator=(SquareGenerator &&) = default;
        SquareGenerator &operator=(const SquareGenerator &) = default;
        ~SquareGenerator() = default;

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
            auto result = sin(2 * M_PI * frequency * t) >= 0.0 ? 1.0 : -1.0;
            counter++;
            return result;
        }

        std::string GetName() override { return "Square"; }
    private:
        float frequency = 1.0f;
        int counter = 0;
        std::shared_ptr<Settings> settings;

    };
}
