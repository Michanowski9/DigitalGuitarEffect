import sys

from PyQt6.QtWidgets import QHBoxLayout, QVBoxLayout, QLabel, QComboBox

sys.path.append("..")
from Effect import Effect

class OverdriveTab(Effect):
    def __init__(self, effectPtr, cpplib):
        Effect.__init__(self, effectPtr, cpplib)

        self.algorithm_combo = QComboBox()

        algorithms = []
        for alg_id in range(self.cpplib.Overdrive_GetAlgorithmsNo(self.effectPtr)):
            algorithms.append(self.cpplib.Overdrive_GetAlgorithmName(self.effectPtr, alg_id))
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

        self.dials = QHBoxLayout()
        self.dials.addLayout(gain_layout)
        self.dials.addLayout(minValue_layout)
        self.dials.addLayout(maxValue_layout)


    def SetLayout(self):
        mainLayout = QVBoxLayout()

        mainLayout.addWidget(self.on_off_button)

        mainLayout.addWidget(QLabel("Algorithm"))
        mainLayout.addWidget(self.algorithm_combo)

        mainLayout.addLayout(self.dials)
        mainLayout.addWidget(self.canvas)
        mainLayout.addWidget(self.visualizationInput_combo)

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


    def algorithm_combo_changed(self):
        self.cpplib.Overdrive_SetAlgorithm(self.effectPtr, self.algorithm_combo.currentIndex())
        self.draw_plot()
