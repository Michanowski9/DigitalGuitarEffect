#ifndef C_INTERFACE_H
#define C_INTERFACE_H

#include <memory>
#include <vector>

#include "mainProgram.h"
#include "Effects/overdrive.h"
#include "Effects/delay.h"

#include "IEffect.h"
#include <memory>

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
        void SetEffectOn(void* ptr, bool value);

    DLL_EXPORT
        void CalculateExampleData(void* ptr, int size, float* data);

    DLL_EXPORT
        void RemoveEffect(void* ptr);

    DLL_EXPORT
        void SwapEffects(int firstId, int secondId);



    DLL_EXPORT
        int Overdrive_GetAlgorithmsNo(void* ptr);

    std::shared_ptr<std::string> result;
    DLL_EXPORT
        const char* Overdrive_GetAlgorithmName(void* ptr, int id);

    DLL_EXPORT
        void Overdrive_SetGain(void* ptr, float data);

    DLL_EXPORT
        void Overdrive_SetMinMaxValue(void* ptr, float minValue, float maxValue);

    DLL_EXPORT
        void Overdrive_SetSoftCutValue(void* ptr, float value);

    DLL_EXPORT
        void Overdrive_SetAlgorithm(void* ptr, int algorithm);


    DLL_EXPORT
        void Delay_SetDelay(void* ptr, int value);

    DLL_EXPORT
        void Delay_SetAlpha(void* ptr, float value);

}

#endif
