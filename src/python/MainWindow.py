from PyQt6.QtWidgets import QHBoxLayout, QVBoxLayout, QTabWidget, QWidget, QPushButton

from CppLibWrapper import CppLib
from SettingsTab import SettingsTab

class MainWindow(QWidget):
    def __init__(self):
        QWidget.__init__(self)

        # cpp lib wrapper
        self.cpplib = CppLib()

        # main window settings
        self.setWindowTitle("Digital Guitar Effect - M. Soja, A. Sałata 2023")
        self.resize(500,500)

        self.bypass = False

        # gui
        self.tab = QTabWidget(self)
        self.AddSettingsTab()

        self.SetShortcuts()
        self.SetButtons()
        self.SetLayout()

        self.show()


    def SetShortcuts(self):
        pass


    def AddSettingsTab(self):
        self.settingsTab = SettingsTab(self.cpplib)
        self.tab.addTab(self.settingsTab, "Settings")


    def SetButtons(self):
        self.start_button = self.MakeButton('Start', self.start_button_on_click)
        self.stop_button = self.MakeButton('Stop', self.stop_button_on_click)
        self.stop_button.setEnabled(False)
        self.bypass_button = self.MakeButton('ByPass', self.bypass_button_on_click)
        self.bypass_button.setEnabled(False)


    def SetLayout(self):
        mainLayout = QVBoxLayout()

        mainButtons = QHBoxLayout()
        mainButtons.addWidget(self.start_button)
        mainButtons.addWidget(self.stop_button)
        mainButtons.addWidget(self.bypass_button)

        mainLayout.addLayout(mainButtons)
        mainLayout.addWidget(self.tab)

        self.setLayout(mainLayout)


    def MakeButton(self, text, func):
        result = QPushButton(text, self)
        result.clicked.connect(func)
        return result


#######################################################
###                 buttons handlers                ###
#######################################################

    def start_button_on_click(self):
        self.start_button.setStyleSheet("background-color: #00ff00")
        self.start_button.setEnabled(False)
        self.stop_button.setEnabled(True)
        self.bypass_button.setEnabled(True)

        inputIndex = self.settingsTab.GetInputIndex()
        outputIndex = self.settingsTab.GetOutputIndex()
        sampleRates = self.settingsTab.GetSampleRates()
        self.cpplib.Start(inputIndex, outputIndex, sampleRates)


    def stop_button_on_click(self):
        self.start_button.setStyleSheet("background-color: light gray")
        self.start_button.setEnabled(True)
        self.stop_button.setEnabled(False)

        self.bypass = False
        self.bypass_button.setStyleSheet("background-color: light gray")
        self.bypass_button.setEnabled(False)

        self.cpplib.Stop()


    def bypass_button_on_click(self):
        self.bypass = not self.bypass
        if self.bypass:
            self.bypass_button.setStyleSheet("background-color: #00ff00")
        else:
            self.bypass_button.setStyleSheet("background-color: light gray")
        self.cpplib.BypassSwitch(self.bypass)


