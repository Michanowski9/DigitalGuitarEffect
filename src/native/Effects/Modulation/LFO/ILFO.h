#pragma once

namespace Modulation {
    class ILFO {
    public:
        virtual float GetNextValue() = 0;
        virtual void ResetCounter() = 0;
        virtual void SetFrequency(const float value) { };
        virtual bool IsUsingFrequency() { return false; }
    };
}
