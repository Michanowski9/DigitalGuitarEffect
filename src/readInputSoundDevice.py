import sounddevice as sd


class ReadInput:
    @staticmethod
    def get_devices():
        s = sd.query_devices()

        return s




