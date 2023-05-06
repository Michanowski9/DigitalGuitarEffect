import sounddevice as sd


class ReadInput:
    @staticmethod
    def get_devices():
        return sd.query_devices()

    @staticmethod
    def get_input_devices():
        devices = str(ReadInput.get_devices()).split("\n")
        output = ""
        for device in devices:
            if "0 in" not in device:
                output += str(device) + "\n"
        return output

    @staticmethod
    def get_output_devices():
        devices = str(ReadInput.get_devices()).split("\n")
        output = ""
        for device in devices:
            if "0 in" in device:
                output += str(device) + "\n"
        return output

