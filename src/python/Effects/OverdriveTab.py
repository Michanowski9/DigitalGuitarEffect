import sys

from PyQt6.QtWidgets import QHBoxLayout, QVBoxLayout, QLabel, QComboBox

sys.path.append("..")
from Effect import Effect

class OverdriveTab(Effect):
    def __init__(self, effectPtr, cpplib):
        Effect.__init__(self, effectPtr, cpplib)

        self.algorithm_combo = QComboBox()

        # list MUST match list order in cpp
        algorithms = [
                "Hard Clipping",
                "Soft Clipping (TODO: correct algorithm)",
                "Fuzz (TODO: correct algorithm)",
                "Distortion - Sav shape (NotImplemented)",
                "Hyperbolic Tangent"
                ]

        self.algorithm_combo.addItems(algorithms)
        self.algorithm_combo.currentTextChanged.connect(self.algorithm_combo_changed)

        self.SetDials()
        self.SetLayout()
        self.algorithm_combo_changed()


    def SetDials(self):
        _, _, self.gain_edit, gain_layout = self.CreateDial("Gain", 0, 10, 1)
        self.gain_edit.textChanged.connect(self.gain_edit_changed_value)

        _, _, self.minValue_edit, minValue_layout = self.CreateDial("Min Value", -1, 1, -1)
        self.minValue_edit.textChanged.connect(self.min_max_refresh)

        _, _, self.maxValue_edit, maxValue_layout = self.CreateDial("Max Value", -1, 1, 1)
        self.maxValue_edit.textChanged.connect(self.min_max_refresh)

        _, self.softCut_dial, self.softCut_edit, softCut_layout = self.CreateDial("Soft Cut", 0, 1, 0.1)
        self.softCut_edit.textChanged.connect(self.soft_cut_refresh)


        self.dials = QHBoxLayout()
        self.dials.addLayout(gain_layout)
        self.dials.addLayout(minValue_layout)
        self.dials.addLayout(maxValue_layout)
        self.dials.addLayout(softCut_layout)


    def SetLayout(self):
        mainLayout = QVBoxLayout()

        mainLayout.addWidget(self.on_off_button)

        mainLayout.addWidget(QLabel("Algorithm"))
        mainLayout.addWidget(self.algorithm_combo)

        mainLayout.addLayout(self.dials)
        mainLayout.addWidget(self.canvas)

        self.setLayout(mainLayout)


    def gain_edit_changed_value(self):
        try:
            gain = float(self.gain_edit.text())
        except ValueError:
            return

        self.cpplib.Overdrive_SetGain(self.effectPtr, gain)
        self.draw_plot()

    def min_max_refresh(self):
        try:
            minValue = float(self.minValue_edit.text())
            maxValue = float(self.maxValue_edit.text())
        except ValueError:
            return

        self.cpplib.Overdrive_SetMinMaxValue(self.effectPtr, minValue, maxValue)
        self.draw_plot()

    def soft_cut_refresh(self):
        try:
            softCut = float(self.softCut_edit.text())
        except ValueError:
            return

        self.cpplib.Overdrive_SetSoftCutValue(self.effectPtr, softCut)
        self.draw_plot()

    def setEnabled_dial(self, edit, dial, value):
        edit.setEnabled(value)
        dial.setEnabled(value)

    def algorithm_combo_changed(self):
        if self.algorithm_combo.currentIndex() == 0: # hard clipping
            self.setEnabled_dial(self.softCut_edit, self.softCut_dial, False)
        elif self.algorithm_combo.currentIndex() == 1: # soft clipping
            self.setEnabled_dial(self.softCut_edit, self.softCut_dial, True)
        elif self.algorithm_combo.currentIndex() == 2: # fuzz
            self.setEnabled_dial(self.softCut_edit, self.softCut_dial, False)
        elif self.algorithm_combo.currentIndex() == 2: # sav shape
            raise NotImplementedError
        elif self.algorithm_combo.currentIndex() == 4: # tanh
            self.setEnabled_dial(self.softCut_edit, self.softCut_dial, False)
        else:
            raise NotImplementedError

        self.cpplib.Overdrive_SetAlgorithm(self.effectPtr, self.algorithm_combo.currentIndex())
        self.draw_plot()
