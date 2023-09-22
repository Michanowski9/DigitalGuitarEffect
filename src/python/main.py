import ctypes
import os
import sys

from PyQt6.QtWidgets import QApplication

from MainWindow import MainWindow

def initLibrary():
    if os.name == 'nt':
        cpplib_path = os.path.join("bin", "Release", "app_lib.dll")
    else:
        cpplib_path = os.path.join("bin", "libapp_lib.so")

    cpplib = ctypes.CDLL(cpplib_path)

#    cpplib.main()


def main():
    #initLibrary()

    app = QApplication([])#sys.argv)
    mainWindow = MainWindow()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()

