#pragma once

class Settings
{
public:
    const int GetCurrentSampleRate()
    {
        return currentSampleRate;
    };

    void SetCurrentSampleRate(const int value)
    {
        currentSampleRate = value;
    };

private:
    int currentSampleRate = 192000;
};
