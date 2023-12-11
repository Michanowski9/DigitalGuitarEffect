#include "cInterface.h"

void InitPA()
{
    mainProgram = std::make_shared<MainProgram>();
}

void FreePA()
{
    mainProgram.reset();
}

int GetDeviceNumber()
{
    return mainProgram->GetDevicesNumber();
}

const char* GetDeviceName(int deviceId)
{
    return mainProgram->GetDevice(deviceId).name.c_str();
}

int GetInputChannelsCount(int deviceId)
{
    return mainProgram->GetDevice(deviceId).inChannels;
}

int GetOutputChannelsCount(int deviceId)
{
    return mainProgram->GetDevice(deviceId).outChannels;
}

double GetInputLowLatency(int deviceId)
{
    return mainProgram->GetDevice(deviceId).inLowLatency;
}

double GetInputHighLatency(int deviceId)
{
    return mainProgram->GetDevice(deviceId).inHighLatency;
}

double GetOutputLowLatency(int deviceId)
{
    return mainProgram->GetDevice(deviceId).outLowLatency;
}

double GetOutputHighLatency(int deviceId)
{
    return mainProgram->GetDevice(deviceId).outLowLatency;
}

int* GetSampleRates(int inputDeviceId, int outputDeviceId)
{
    auto sampleRates = mainProgram->GetSampleRates(inputDeviceId, outputDeviceId);

    int* result = new int[sampleRates.size() + 1];
    result[0] = sampleRates.size();
    for(int i = 0; i < sampleRates.size(); i++)
    {
        result[i + 1] = sampleRates[i];
    }
    return result;
}

void FreeArray(int* ptr)
{
    delete[] ptr;
}

void Start(int inputDeviceId, int outputDeviceId, int sampleRate)
{
    mainProgram->StartStream(inputDeviceId, outputDeviceId, sampleRate);
}

void Stop()
{
    mainProgram->StopStream();
}

void BypassSwitch(bool value)
{
    mainProgram->SetBypass(value);
}

void* AddEffectOverdrive()
{
    auto effect = std::make_shared<Overdrive::Overdrive>();

    effect->AddAlgorithm(std::make_shared<Overdrive::HardClipping>());
    effect->AddAlgorithm(std::make_shared<Overdrive::HyperbolicTangent>());
    effect->AddAlgorithm(std::make_shared<Overdrive::Exponential>());

    return mainProgram->AddEffect(effect);
}

void* AddEffectDelay()
{
    return mainProgram->AddEffect(
            std::make_shared<Delay::Delay>(Delay::Delay(
                {
                    { std::make_shared<Delay::CombFilter>(), std::make_shared<Delay::CombFilter>() },
                    { std::make_shared<Delay::RecursiveCombFilter>(), std::make_shared<Delay::RecursiveCombFilter>() },
                    { std::make_shared<Delay::PingPong>(), std::make_shared<Delay::PingPong>() }
                }
                )));
}

void* AddEffectModulation()
{
    auto visualisationSettings = std::make_shared<Settings>();
    visualisationSettings->SetCurrentSampleRate(1000);
    return mainProgram->AddEffect(
            std::make_shared<Modulation::Modulation>(Modulation::Modulation(
                {
                    { std::make_shared<Modulation::Chorus>(), std::make_shared<Modulation::Chorus>() },
                    { std::make_shared<Modulation::Flanger>(), std::make_shared<Modulation::Flanger>() }
                },
                {
                    { std::make_shared<Modulation::TriangleGenerator>(mainProgram->GetSettings()), std::make_shared<Modulation::TriangleGenerator>(visualisationSettings) },
                    { std::make_shared<Modulation::SinusGenerator>(mainProgram->GetSettings()), std::make_shared<Modulation::SinusGenerator>(visualisationSettings) },
                    { std::make_shared<Modulation::SquareGenerator>(mainProgram->GetSettings()), std::make_shared<Modulation::SquareGenerator>(visualisationSettings) }
                }
                )));
}


void SetEffectOn(void* ptr, bool value)
{
    static_cast<IEffect*>(ptr)->SetOn(value);
}

void CalculateExampleData(void* ptr, int size, float* dataLeft, float* dataRight)
{
    static_cast<IEffect*>(ptr)->ResetEffect();
    for(auto i = 0; i < size; i++)
    {
        StereoSample input{dataLeft[i], dataRight[i]};
        StereoSample output{0, 0};
        static_cast<IEffect*>(ptr)->CalculateForVisualization(output,input);
        dataLeft[i] = output.left;
        dataRight[i] = output.right;
    }
}

void RemoveEffect(void* ptr)
{
    mainProgram->RemoveEffect(ptr);
}

void SwapEffects(int firstId, int secondId)
{
    mainProgram->SwapEffects(firstId, secondId);
}

void Overdrive_SetGain(void* ptr, float value)
{
    static_cast<Overdrive::Overdrive*>(ptr)->SetGain(value);
}

void Overdrive_SetMinMaxValue(void* ptr, float minValue, float maxValue)
{
    static_cast<Overdrive::Overdrive*>(ptr)->SetMinValue(minValue);
    static_cast<Overdrive::Overdrive*>(ptr)->SetMaxValue(maxValue);
}

void Overdrive_SetOffset(void* ptr, float value)
{
    static_cast<Overdrive::Overdrive*>(ptr)->SetOffset(value);
}


bool Overdrive_IsUsingGain(void* ptr)
{
    return static_cast<Overdrive::Overdrive*>(ptr)->IsUsingGain();
}

bool Overdrive_IsUsingMinValue(void* ptr)
{
    return static_cast<Overdrive::Overdrive*>(ptr)->IsUsingMinValue();
}

bool Overdrive_IsUsingMaxValue(void* ptr)
{
    return static_cast<Overdrive::Overdrive*>(ptr)->IsUsingMaxValue();
}

bool Overdrive_IsUsingOffset(void* ptr)
{
    return static_cast<Overdrive::Overdrive*>(ptr)->IsUsingOffset();
}

void Delay_SetDelay(void* ptr, int value)
{
    static_cast<Delay::Delay*>(ptr)->SetDelayInMilliseconds(value);
}

bool Delay_IsUsingDelay(void* ptr)
{
    return static_cast<Delay::Delay*>(ptr)->IsUsingDelay();
}


bool Delay_IsUsingAlpha(void* ptr)
{
    return static_cast<Delay::Delay*>(ptr)->IsUsingAlpha();
}


bool Delay_IsUsingLeftInputVolume(void* ptr)
{
    return static_cast<Delay::Delay*>(ptr)->IsUsingLeftInputVolume();
}


bool Delay_IsUsingRightInputVolume(void* ptr)
{
    return static_cast<Delay::Delay*>(ptr)->IsUsingRightInputVolume();
}


bool Delay_IsUsingFeedback(void* ptr)
{
    return static_cast<Delay::Delay*>(ptr)->IsUsingFeedback();
}


void Delay_SetFeedback(void* ptr, float value)
{
    static_cast<Delay::Delay*>(ptr)->SetFeedback(value);
}


void Delay_SetLeftInputVolume(void* ptr, float value)
{
    static_cast<Delay::Delay*>(ptr)->SetLeftInputVolume(value);
}


void Delay_SetRightInputVolume(void* ptr, float value)
{
    static_cast<Delay::Delay*>(ptr)->SetRightInputVolume(value);
}


void Delay_SetAlpha(void* ptr, float value)
{
    static_cast<Delay::Delay*>(ptr)->SetAlpha(value);
}

int Effect_GetAlgorithmsNo(void* ptr)
{
    return static_cast<IEffect*>(ptr)->GetAlgorithmsNo();
}

const char* Effect_GetAlgorithmName(void* ptr, int id)
{
    result = std::make_shared<std::string>(static_cast<IEffect*>(ptr)->GetAlgorithmName(id));
    return result->c_str();
}

void Effect_SetAlgorithm(void* ptr, int algorithm)
{
    static_cast<IEffect*>(ptr)->SetAlgorithm(algorithm);
}

void Modulation_SetDelay(void* ptr, int value)
{
    static_cast<Modulation::Modulation*>(ptr)->SetDelayInMilliseconds(value);
}

void Modulation_SetAlpha(void* ptr, float value)
{
    static_cast<Modulation::Modulation*>(ptr)->SetAlpha(value);
}


void Modulation_SetFeedback(void* ptr, float value)
{
    static_cast<Modulation::Modulation*>(ptr)->SetFeedback(value);
}

void Modulation_SetDepth(void* ptr, float value)
{
    static_cast<Modulation::Modulation*>(ptr)->SetDepth(value);
}

void Modulation_SetLFOFrequency(void* ptr, float value)
{
    static_cast<Modulation::Modulation*>(ptr)->SetLFOFrequency(value);
}


bool Modulation_IsUsingDelay(void* ptr)
{
    return static_cast<Modulation::Modulation*>(ptr)->IsUsingDelay();
}
bool Modulation_IsUsingAlpha(void* ptr)
{
    return static_cast<Modulation::Modulation*>(ptr)->IsUsingAlpha();
}
bool Modulation_IsUsingFeedback(void* ptr)
{
    return static_cast<Modulation::Modulation*>(ptr)->IsUsingFeedback();
}
bool Modulation_IsUsingDepth(void* ptr)
{
    return static_cast<Modulation::Modulation*>(ptr)->IsUsingDepth();
}
bool Modulation_IsUsingLFOFrequency(void* ptr)
{
    return static_cast<Modulation::Modulation*>(ptr)->IsUsingLFOFrequency();
}

int Modulation_GetLFOsNo(void* ptr)
{
    return static_cast<Modulation::Modulation*>(ptr)->GetLFOsNo();
}

const char* Modulation_GetLFOName(void* ptr, int id)
{
    result = std::make_shared<std::string>(static_cast<Modulation::Modulation*>(ptr)->GetLFOName(id));
    return result->c_str();
}

void Modulation_SetLFO(void* ptr, int lfo)
{
    static_cast<Modulation::Modulation*>(ptr)->SetLFO(lfo);
}
