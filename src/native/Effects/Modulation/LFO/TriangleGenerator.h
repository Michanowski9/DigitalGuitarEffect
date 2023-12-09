#pragma once

#include "ILFO.h"
#include "../../../Settings.h"
#include <cmath>
#include <memory>
#include <iostream>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

namespace Modulation {
    class TriangleGenerator : public ILFO {
    public:
        TriangleGenerator(std::shared_ptr<Settings> settings)
            :settings(settings)
        {

        };
        TriangleGenerator(TriangleGenerator &&) = default;
        TriangleGenerator(const TriangleGenerator &) = default;
        TriangleGenerator &operator=(TriangleGenerator &&) = default;
        TriangleGenerator &operator=(const TriangleGenerator &) = default;
        ~TriangleGenerator() = default;

        void SetFrequency(const float value) override
        {
            frequency = value;
        }

        void ResetCounter() override {
            counter = 0;
        }

        float GetNextValue() override {
            auto t = static_cast<float>(counter) / settings->GetCurrentSampleRate();
            auto sinValue = std::sin(2 * M_PI * frequency * t);
            auto result = 2 * std::asin(sinValue) / M_PI;
            counter++;
            return static_cast<float>(std::round(result*1.0e10) / 1.0e10);
        }
    private:
        float frequency = 1.0f;
        int counter = 0;
        std::shared_ptr<Settings> settings;

    };
}
