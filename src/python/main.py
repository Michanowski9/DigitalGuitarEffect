import sys

from PyQt6.QtWidgets import QApplication

from MainWindow import MainWindow

def main():
    pass
    app = QApplication([])#sys.argv)
    mainWindow = MainWindow()
    sys.exit(app.exec())


if __name__ == "__main__":
    main()

