import ctypes
import os
import numpy as np

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

    def Overdrive_SetAlgorithm(self, ptr, value):
        self.cpplib.Overdrive_SetAlgorithm.argtypes = [ctypes.c_void_p, ctypes.c_int]
        self.cpplib.Overdrive_SetAlgorithm.restype = None

        self.cpplib.Overdrive_SetAlgorithm(ptr, value)
