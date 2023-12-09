import ctypes
import os

class CppLib:
    def __init__(self):
        if os.name == 'nt':
            cpplib_path = os.path.join("bin", "Release", "app_lib.dll")
        else:
            cpplib_path = os.path.join("bin", "libapp_lib.so")

        self.cpplib = ctypes.CDLL(cpplib_path)
        self.cpplib.InitPA()


    def __del__(self):
        self.cpplib.FreePA()


    def GetInputDevices(self):
        result = {}
        for i in range(self.cpplib.GetDeviceNumber()):
            if self.cpplib.GetInputChannelsCount(i) > 0:
                result[i] = self.GetDeviceName(i)
        return result


    def GetOutputDevices(self):
        result = {}
        for i in range(self.cpplib.GetDeviceNumber()):
            if self.cpplib.GetOutputChannelsCount(i) > 0:
                result[i] = self.GetDeviceName(i)
        return result


    def GetSampleRates(self, inputIndex, outputIndex):
        self.cpplib.GetSampleRates.restype = ctypes.POINTER(ctypes.c_int)
        cppresult = self.cpplib.GetSampleRates(inputIndex, outputIndex)

        size = cppresult[0]
        result = []
        for i in range(0, size):
            result.append(cppresult[i + 1])
        self.cpplib.FreeArray(cppresult)
        return result


    def Start(self, inputDevice, outputDevice, sampleRate):
        self.cpplib.Start.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int]
        self.cpplib.Start(inputDevice, outputDevice, sampleRate)


    def Stop(self):
        self.cpplib.Stop()


    def GetOutputHighLatency(self, outputDevice):
        self.cpplib.GetOutputHighLatency.restype = ctypes.c_double
        return self.cpplib.GetOutputHighLatency(outputDevice)


    def GetInputHighLatency(self, inputDevice):
        self.cpplib.GetInputHighLatency.restype = ctypes.c_double
        return self.cpplib.GetInputHighLatency(inputDevice)


    def GetOutputLowLatency(self, outputDevice):
        self.cpplib.GetOutputLowLatency.restype = ctypes.c_double
        return self.cpplib.GetOutputLowLatency(outputDevice)


    def GetInputLowLatency(self, inputDevice):
        self.cpplib.GetInputLowLatency.restype = ctypes.c_double
        return self.cpplib.GetInputLowLatency(inputDevice)


    def GetDeviceName(self, deviceId):
        GetDeviceName = self.cpplib.GetDeviceName
        GetDeviceName.restype = ctypes.POINTER(ctypes.c_char_p)
        GetDeviceName.argtypes = [ctypes.c_int]

        deviceName_ptr = GetDeviceName(deviceId)
        deviceName = ctypes.c_char_p.from_buffer(deviceName_ptr)
        return deviceName.value.decode('utf-8')

    def BypassSwitch(self, value):
        self.cpplib.BypassSwitch.argtypes = [ctypes.c_bool]
        self.cpplib.BypassSwitch(value)

    def AddEffect(self, effect):
        if effect == "overdrive":
            self.cpplib.AddEffectOverdrive.restype = ctypes.c_void_p
            return self.cpplib.AddEffectOverdrive()
        elif effect == "delay":
            self.cpplib.AddEffectDelay.restype = ctypes.c_void_p
            return self.cpplib.AddEffectDelay()
        elif effect == "modulation":
            self.cpplib.AddEffectModulation.restype = ctypes.c_void_p
            return self.cpplib.AddEffectModulation()


    def SetEffectOn(self, effectPtr, value):
        self.cpplib.SetEffectOn.argtypes = [ctypes.c_void_p, ctypes.c_bool]
        self.cpplib.SetEffectOn(effectPtr, value)

    def CalculateExampleData(self, effectPtr, data):
        self.cpplib.CalculateExampleData.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.POINTER(ctypes.c_float)]
        dataArray = (ctypes.c_float * len(data))(*data)

        self.cpplib.CalculateExampleData(effectPtr, len(data), dataArray)

        for i in range(len(data)):
            data[i] = dataArray[i]


    def RemoveEffect(self, ptr):
        self.cpplib.RemoveEffect.argtypes = [ctypes.c_void_p]
        self.cpplib.RemoveEffect.restype = None

        self.cpplib.RemoveEffect(ptr)

    def SwapEffects(self, firstId, secondId):
        self.cpplib.SwapEffects.argtypes = [ctypes.c_int32, ctypes.c_int32]
        self.cpplib.SwapEffects.restype = None

        self.cpplib.SwapEffects(firstId, secondId)


    def Overdrive_SetGain(self, ptr, value):
        self.cpplib.Overdrive_SetGain.argtypes = [ctypes.c_void_p, ctypes.c_float]
        self.cpplib.Overdrive_SetGain.restype = None

        self.cpplib.Overdrive_SetGain(ptr, value)


    def Overdrive_SetMinMaxValue(self, ptr, minValue, maxValue):
        self.cpplib.Overdrive_SetMinMaxValue.argtypes = [ctypes.c_void_p, ctypes.c_float, ctypes.c_float]
        self.cpplib.Overdrive_SetMinMaxValue.restype = None

        self.cpplib.Overdrive_SetMinMaxValue(ptr, minValue, maxValue)


    def Overdrive_SetSoftCutValue(self, ptr, value):
        self.cpplib.Overdrive_SetSoftCutValue.argtypes = [ctypes.c_void_p, ctypes.c_float]
        self.cpplib.Overdrive_SetSoftCutValue.restype = None

        self.cpplib.Overdrive_SetSoftCutValue(ptr, value)

    def Overdrive_IsUsingGain(self, ptr):
        self.cpplib.Overdrive_IsUsingGain.argtypes = [ctypes.c_void_p]
        self.cpplib.Overdrive_IsUsingGain.restype = ctypes.c_bool

        return self.cpplib.Overdrive_IsUsingGain(ptr)

    def Overdrive_IsUsingMinValue(self, ptr):
        self.cpplib.Overdrive_IsUsingMinValue.argtypes = [ctypes.c_void_p]
        self.cpplib.Overdrive_IsUsingMinValue.restype = ctypes.c_bool

        return self.cpplib.Overdrive_IsUsingMinValue(ptr)

    def Overdrive_IsUsingMaxValue(self, ptr):
        self.cpplib.Overdrive_IsUsingMaxValue.argtypes = [ctypes.c_void_p]
        self.cpplib.Overdrive_IsUsingMaxValue.restype = ctypes.c_bool

        return self.cpplib.Overdrive_IsUsingMaxValue(ptr)

    def Delay_SetDelay(self, ptr, value):
        self.cpplib.Delay_SetDelay.argtypes = [ctypes.c_void_p, ctypes.c_int]
        self.cpplib.Delay_SetDelay.restype = None

        self.cpplib.Delay_SetDelay(ptr, int(value))

    def Delay_SetAlpha(self, ptr, value):
        self.cpplib.Delay_SetAlpha.argtypes = [ctypes.c_void_p, ctypes.c_float]
        self.cpplib.Delay_SetAlpha.restype = None

        self.cpplib.Delay_SetAlpha(ptr, value)

    def Delay_SetFeedback(self, ptr, value):
        self.cpplib.Delay_SetFeedback.argtypes = [ctypes.c_void_p, ctypes.c_float]
        self.cpplib.Delay_SetFeedback.restype = None

        self.cpplib.Delay_SetFeedback(ptr, value)

    def Delay_IsUsingDelay(self, ptr):
        self.cpplib.Delay_IsUsingDelay.argtypes = [ctypes.c_void_p]
        self.cpplib.Delay_IsUsingDelay.restype = ctypes.c_bool

        return self.cpplib.Delay_IsUsingDelay(ptr)


    def Delay_IsUsingAlpha(self, ptr):
        self.cpplib.Delay_IsUsingAlpha.argtypes = [ctypes.c_void_p]
        self.cpplib.Delay_IsUsingAlpha.restype = ctypes.c_bool

        return self.cpplib.Delay_IsUsingAlpha(ptr)


    def Delay_IsUsingFeedback(self, ptr):
        self.cpplib.Delay_IsUsingFeedback.argtypes = [ctypes.c_void_p]
        self.cpplib.Delay_IsUsingFeedback.restype = ctypes.c_bool

        return self.cpplib.Delay_IsUsingFeedback(ptr)



    def Effect_GetAlgorithmsNo(self, ptr):
        self.cpplib.Effect_GetAlgorithmsNo.argtypes = [ctypes.c_void_p]
        self.cpplib.Effect_GetAlgorithmsNo.restype = ctypes.c_int

        return self.cpplib.Effect_GetAlgorithmsNo(ptr)

    def Effect_GetAlgorithmName(self, ptr, id):
        self.cpplib.Effect_GetAlgorithmName.argtypes = [ctypes.c_void_p, ctypes.c_int]
        self.cpplib.Effect_GetAlgorithmName.restype = ctypes.POINTER(ctypes.c_char_p)

        result_ptr = self.cpplib.Effect_GetAlgorithmName(ptr, id)
        result = ctypes.c_char_p.from_buffer(result_ptr).value.decode('utf-8')
        return result

    def Effect_SetAlgorithm(self, ptr, value):
        self.cpplib.Effect_SetAlgorithm.argtypes = [ctypes.c_void_p, ctypes.c_int]
        self.cpplib.Effect_SetAlgorithm.restype = None

        self.cpplib.Effect_SetAlgorithm(ptr, value)

    def Modulation_SetDelay(self, ptr, value):
        self.cpplib.Modulation_SetDelay.argtypes = [ctypes.c_void_p, ctypes.c_int]
        self.cpplib.Modulation_SetDelay.restype = None

        self.cpplib.Modulation_SetDelay(ptr, int(value))


    def Modulation_SetAlpha(self, ptr, value):
        self.cpplib.Modulation_SetAlpha.argtypes = [ctypes.c_void_p, ctypes.c_float]
        self.cpplib.Modulation_SetAlpha.restype = None

        self.cpplib.Modulation_SetAlpha(ptr, value)

    def Modulation_SetFeedback(self, ptr, value):
        self.cpplib.Modulation_SetFeedback.argtypes = [ctypes.c_void_p, ctypes.c_float]
        self.cpplib.Modulation_SetFeedback.restype = None

        self.cpplib.Modulation_SetFeedback(ptr, value)



    def Modulation_SetDepth(self, ptr, value):
        self.cpplib.Modulation_SetDepth.argtypes = [ctypes.c_void_p, ctypes.c_float]
        self.cpplib.Modulation_SetDepth.restype = None

        self.cpplib.Modulation_SetDepth(ptr, value)


    def Modulation_SetLFOFrequency(self, ptr, value):
        self.cpplib.Modulation_SetLFOFrequency.argtypes = [ctypes.c_void_p, ctypes.c_float]
        self.cpplib.Modulation_SetLFOFrequency.restype = None

        self.cpplib.Modulation_SetLFOFrequency(ptr, value)

    def Modulation_IsUsingDelay(self, ptr):
        self.cpplib.Modulation_IsUsingDelay.argtypes = [ctypes.c_void_p]
        self.cpplib.Modulation_IsUsingDelay.restype = ctypes.c_bool

        return self.cpplib.Modulation_IsUsingDelay(ptr)


    def Modulation_IsUsingAlpha(self, ptr):
        self.cpplib.Modulation_IsUsingAlpha.argtypes = [ctypes.c_void_p]
        self.cpplib.Modulation_IsUsingAlpha.restype = ctypes.c_bool

        return self.cpplib.Modulation_IsUsingAlpha(ptr)


    def Modulation_IsUsingFeedback(self, ptr):
        self.cpplib.Modulation_IsUsingFeedback.argtypes = [ctypes.c_void_p]
        self.cpplib.Modulation_IsUsingFeedback.restype = ctypes.c_bool

        return self.cpplib.Modulation_IsUsingFeedback(ptr)


    def Modulation_IsUsingDepth(self, ptr):
        self.cpplib.Modulation_IsUsingDepth.argtypes = [ctypes.c_void_p]
        self.cpplib.Modulation_IsUsingDepth.restype = ctypes.c_bool

        return self.cpplib.Modulation_IsUsingDepth(ptr)


    def Modulation_IsUsingLFOFrequency(self, ptr):
        self.cpplib.Modulation_IsUsingLFOFrequency.argtypes = [ctypes.c_void_p]
        self.cpplib.Modulation_IsUsingLFOFrequency.restype = ctypes.c_bool

        return self.cpplib.Modulation_IsUsingLFOFrequency(ptr)


