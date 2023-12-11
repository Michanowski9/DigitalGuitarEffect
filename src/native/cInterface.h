#ifndef C_INTERFACE_H
#define C_INTERFACE_H

#include "Effects/Delay/Delay.h"
#include "Effects/Delay/Algorithms/RecursiveCombFilter.h"
#include "Effects/Delay/Algorithms/CombFilter.h"
#include "Effects/Delay/Algorithms/PingPong.h"

#include "Effects/IEffect.h"

#include "Effects/Modulation/Algorithms/Chorus.h"
#include "Effects/Modulation/Algorithms/Flanger.h"
#include "Effects/Modulation/LFO/TriangleGenerator.h"
#include "Effects/Modulation/LFO/SinusGenerator.h"
#include "Effects/Modulation/LFO/SquareGenerator.h"
#include "Effects/Modulation/Modulation.h"

#include "Effects/Overdrive/Algorithms/Exponential.h"
#include "Effects/Overdrive/Algorithms/HardClipping.h"
#include "Effects/Overdrive/Algorithms/HyperbolicTangent.h"
#include "Effects/Overdrive/Algorithms/IAlgorithm.h"
#include "Effects/Overdrive/Overdrive.h"

#include "mainProgram.h"
#include "Settings.h"

#include <memory>
#include <vector>

std::shared_ptr<MainProgram> mainProgram;

#if defined (WIN32)
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT
#endif

extern "C"
{
    DLL_EXPORT
        void InitPA();

    DLL_EXPORT
        void FreePA();

    DLL_EXPORT
        int GetDeviceNumber();

    DLL_EXPORT
        const char* GetDeviceName(int device);

    DLL_EXPORT
        int GetInputChannelsCount(int device);

    DLL_EXPORT
        int GetOutputChannelsCount(int device);

    DLL_EXPORT
        double GetInputLowLatency(int inputDevice);

    DLL_EXPORT
        double GetOutputLowLatency(int outputDevice);

    DLL_EXPORT
        double GetInputHighLatency(int inputDevice);

    DLL_EXPORT
        double GetOutputHighLatency(int outputDevice);

    DLL_EXPORT
        int* GetSampleRates(int inputDevice, int outputDevice);

    DLL_EXPORT
        void FreeArray(int* ptr);

    DLL_EXPORT
        void Start(int inputDevice, int outputDevice, int sampleRate);

    DLL_EXPORT
        void Stop();

    DLL_EXPORT
        void BypassSwitch(bool value);

    DLL_EXPORT
        void* AddEffectOverdrive();

    DLL_EXPORT
        void* AddEffectDelay();

    DLL_EXPORT
        void* AddEffectModulation();


    DLL_EXPORT
        void SetEffectOn(void* ptr, bool value);

    DLL_EXPORT
        void CalculateExampleData(void* ptr, int size, float* dataLeft, float* dataRight);

    DLL_EXPORT
        void RemoveEffect(void* ptr);

    DLL_EXPORT
        void SwapEffects(int firstId, int secondId);


    DLL_EXPORT
        void Overdrive_SetGain(void* ptr, float data);

    DLL_EXPORT
        void Overdrive_SetMinMaxValue(void* ptr, float minValue, float maxValue);

    DLL_EXPORT
        void Overdrive_SetOffset(void* ptr, float data);


    DLL_EXPORT
        bool Overdrive_IsUsingMinValue(void* ptr);

    DLL_EXPORT
        bool Overdrive_IsUsingMaxValue(void* ptr);

    DLL_EXPORT
        bool Overdrive_IsUsingGain(void* ptr);

    DLL_EXPORT
        bool Overdrive_IsUsingOffset(void* ptr);


    DLL_EXPORT
        void Delay_SetDelay(void* ptr, int value);

    DLL_EXPORT
        void Delay_SetAlpha(void* ptr, float value);

    DLL_EXPORT
        void Delay_SetFeedback(void* ptr, float value);
    DLL_EXPORT
        void Delay_SetLeftInputVolume(void* ptr, float value);
    DLL_EXPORT
        void Delay_SetRightInputVolume(void* ptr, float value);




    DLL_EXPORT
        bool Delay_IsUsingDelay(void* ptr);

    DLL_EXPORT
        bool Delay_IsUsingAlpha(void* ptr);

    DLL_EXPORT
        bool Delay_IsUsingFeedback(void* ptr);
    DLL_EXPORT
        bool Delay_IsUsingLeftInputVolume(void* ptr);
    DLL_EXPORT
        bool Delay_IsUsingRightInputVolume(void* ptr);



    DLL_EXPORT
        int Effect_GetAlgorithmsNo(void* ptr);

    DLL_EXPORT
        const char* Effect_GetAlgorithmName(void* ptr, int id);

    DLL_EXPORT
        void Effect_SetAlgorithm(void* ptr, int algorithm);


    DLL_EXPORT
        void Modulation_SetDelay(void* ptr, int value);

    DLL_EXPORT
        void Modulation_SetAlpha(void* ptr, float value);
    DLL_EXPORT
        void Modulation_SetFeedback(void* ptr, float value);


    DLL_EXPORT
        void Modulation_SetDepth(void* ptr, float value);

    DLL_EXPORT
        void Modulation_SetLFOFrequency(void* ptr, float value);

    DLL_EXPORT
        bool Modulation_IsUsingDelay(void* ptr);
    DLL_EXPORT
        bool Modulation_IsUsingAlpha(void* ptr);
    DLL_EXPORT
        bool Modulation_IsUsingFeedback(void* ptr);
    DLL_EXPORT
        bool Modulation_IsUsingDepth(void* ptr);
    DLL_EXPORT
        bool Modulation_IsUsingLFOFrequency(void* ptr);
    DLL_EXPORT
        int Modulation_GetLFOsNo(void* ptr);

    DLL_EXPORT
        const char* Modulation_GetLFOName(void* ptr, int id);

    DLL_EXPORT
        void Modulation_SetLFO(void* ptr, int lfo);








    std::shared_ptr<std::string> result;



}

#endif
