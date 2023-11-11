from PyQt6.QtWidgets import QHBoxLayout, QVBoxLayout, QTabWidget, QWidget, QPushButton, QDialog

from CppLibWrapper import CppLib
from SettingsTab import SettingsTab
from ChooseEffectDialog import ChooseEffectDialog
from Effects.OverdriveTab import OverdriveTab
from Effects.DelayTab import DelayTab

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

        self.tab.currentChanged.connect(self.tab_current_changed)

        self.show()


    def SetShortcuts(self):
        pass


    def AddSettingsTab(self):
        self.settingsTab = SettingsTab(self.cpplib)
        self.tab.addTab(self.settingsTab, "Settings")


    def SetButtons(self):
        self.start_button = self.MakeButton('Start', self.start_button_on_click)
        self.stop_button = self.MakeButton('Stop', self.stop_button_on_click, enabled=False)
        self.bypass_button = self.MakeButton('ByPass', self.bypass_button_on_click, enabled=False)

        self.add_effect_button = self.MakeButton('Add Efect', self.add_effect_button_on_click)
        self.remove_effect_button = self.MakeButton('Remove Efect', self.remove_effect_button_on_click, enabled=False)
        self.move_left_effect_button = self.MakeButton('< Move Left', self.move_left_effect_button_on_click, enabled=False)
        self.move_right_effect_button = self.MakeButton('Move Right >', self.move_right_effect_button_on_click, enabled=False)


    def SetLayout(self):
        mainLayout = QVBoxLayout()

        mainButtons = QHBoxLayout()
        mainButtons.addWidget(self.start_button)
        mainButtons.addWidget(self.stop_button)
        mainButtons.addWidget(self.bypass_button)

        effectButtons = QHBoxLayout()
        effectButtons.addWidget(self.add_effect_button)
        effectButtons.addWidget(self.remove_effect_button)
        effectButtons.addWidget(self.move_left_effect_button)
        effectButtons.addWidget(self.move_right_effect_button)

        mainLayout.addLayout(mainButtons)
        mainLayout.addLayout(effectButtons)
        mainLayout.addWidget(self.tab)

        self.setLayout(mainLayout)


    def MakeButton(self, text, func, enabled=True):
        result = QPushButton(text, self)
        result.clicked.connect(func)
        result.setEnabled(enabled)
        return result


    def tab_current_changed(self, i):
        if i == 0:
            self.remove_effect_button.setEnabled(False)
        else:
            self.remove_effect_button.setEnabled(True)

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
        self.cpplib.BypassSwitch(self.bypass)

        self.cpplib.Stop()


    def bypass_button_on_click(self):
        self.bypass = not self.bypass
        if self.bypass:
            self.bypass_button.setStyleSheet("background-color: #00ff00")
        else:
            self.bypass_button.setStyleSheet("background-color: light gray")
        self.cpplib.BypassSwitch(self.bypass)


    def add_effect_button_on_click(self):
        dialog = ChooseEffectDialog()

        if not dialog.exec():
            return

        match dialog.result:
            case "Overdrive":
                effectPtr = self.cpplib.AddEffect("overdrive")
                indexTab = self.tab.addTab(OverdriveTab(effectPtr, self.cpplib), "Overdrive")
            case "Delay":
                effectPtr = self.cpplib.AddEffect("delay")
                indexTab = self.tab.addTab(DelayTab(effectPtr, self.cpplib), "Delay")
        self.tab.setCurrentIndex(indexTab)


    def remove_effect_button_on_click(self):
        currentTab = self.tab.currentWidget()
        currentTab.RemoveEffect()
        self.tab.removeTab(self.tab.currentIndex())


    def move_left_effect_button_on_click(self):
        raise NotImplementedError


    def move_right_effect_button_on_click(self):
        raise NotImplementedError

