import pyaudio as pyaudio
import wave

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

    @staticmethod
    def play(input_id, output_id):
        chunk = 1024
        sample_format = pyaudio.paInt16
        channels = 2
        fs = 44100
        seconds = 3

        p = pyaudio.PyAudio()

        print('Playing')
        streamIn = p.open(format=sample_format,
                          channels=channels,
                          rate=fs,
                          frames_per_buffer=chunk,
                          input=True,
                          input_device_index=input_id)

        streamOut = p.open(format=sample_format,
                           channels=channels,
                           rate=fs,
                           frames_per_buffer=chunk,
                           output=True,
                           input_device_index=output_id)

        for i in range(0, int(fs / chunk * seconds)):
            data = streamIn.read(chunk)

            #transform(data)

            streamOut.write(data)

        streamIn.stop_stream()
        streamIn.close()
        p.terminate()

    @staticmethod
    def record(filename, device_id):
        chunk = 1024
        sample_format = pyaudio.paInt16
        channels = 2
        fs = 44100
        seconds = 3

        p = pyaudio.PyAudio()

        print('Recording')

        stream = p.open(format=sample_format,
                        channels=channels,
                        rate=fs,
                        frames_per_buffer=chunk,
                        input=True,
                        input_device_index=device_id)

        frames = []

        for i in range(0, int(fs / chunk * seconds)):
            data = stream.read(chunk)
            print(data, end="")
            frames.append(data)

        stream.stop_stream()
        stream.close()
        p.terminate()

        print('Finished recording')

        wf = wave.open(filename, 'wb')
        wf.setnchannels(channels)
        wf.setsampwidth(p.get_sample_size(sample_format))
        wf.setframerate(fs)
        wf.writeframes(b''.join(frames))
        wf.close()
