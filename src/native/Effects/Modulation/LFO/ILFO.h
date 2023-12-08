#pragma once

class ILFO {
public:
    virtual float GetNextValue() = 0;
    virtual void SetFrequency(const float value) = 0;
    virtual void ResetCounter() = 0;
};
