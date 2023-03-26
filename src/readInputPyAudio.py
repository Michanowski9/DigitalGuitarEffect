import pyaudio as pyaudio


class ReadInput:
    @staticmethod
    def get_devices():
        p = pyaudio.PyAudio()

        result = []
        for i in range(p.get_device_count()):
            device_info = p.get_device_info_by_index(i)
            result.append(device_info)
        return result

    @staticmethod
    def get_input():
        p = pyaudio.PyAudio()

        result = []

        for i in range(p.get_device_count()):
            device_info = p.get_device_info_by_index(i)
            if device_info["maxInputChannels"] > 0:
                result.append(device_info)
        return result
