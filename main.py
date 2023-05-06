import src.readInputPyAudio as pyaudio
import src.readInputSoundDevice as sounddevice


def main():
    py_audio = pyaudio.ReadInput()
    # print(py_audio.get_devices())
    sc = sounddevice.ReadInput()

    print("Input Devices:")
    print(sc.get_input_devices())
    print("Output Devices:")
    print(sc.get_output_devices())

    input_device = int(input("Choose input device: "))
    output_device = int(input("Choose output device: "))
    py_audio.play(input_device, output_device)

    # py_audio.record("wave.wav", 25)


if __name__ == "__main__":
    main()
