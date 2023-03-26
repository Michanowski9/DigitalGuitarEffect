from src.readInputPyAudio import ReadInput as ReadInputPyAudio
from src.readInputSoundDevice import ReadInput as ReadInputSoundDevice


def main():
    py_audio = ReadInputPyAudio()
    sc = ReadInputSoundDevice()
    print(py_audio.get_devices())
    print(sc.get_devices())


if __name__ == "__main__":
    main()
