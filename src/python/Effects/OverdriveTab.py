import sys

from PyQt6.QtWidgets import QLabel, QComboBox

sys.path.append("..")
from Effect import Effect

class OverdriveTab(Effect):
    def __init__(self, effectPtr, cpplib):
        Effect.__init__(self, effectPtr, cpplib)

        self.SetEffectSettings()
        self.SetDials()
        self.algorithm_combo_changed()


    def SetEffectSettings(self):
        self.algorithm_combo = QComboBox()

        algorithms = []
        for alg_id in range(self.cpplib.Effect_GetAlgorithmsNo(self.effectPtr)):
            algorithms.append(self.cpplib.Effect_GetAlgorithmName(self.effectPtr, alg_id))
        self.algorithm_combo.addItems(algorithms)
        self.algorithm_combo.currentTextChanged.connect(self.algorithm_combo_changed)

        self.SetEffectLayout()


    def SetEffectLayout(self):
        self.effect_settings.addWidget(QLabel("Algorithm:"))
        self.effect_settings.addWidget(self.algorithm_combo)


    def SetDials(self):
        self.gain_controll = self.CreateDial("Gain", 0, 10, 1)
        self.gain_controll.edit.textChanged.connect(self.gain_edit_changed_value)

        self.minValue_controll = self.CreateDial("Min Value", -1, 1, -1)
        self.minValue_controll.edit.textChanged.connect(self.min_max_refresh)

        self.maxValue_controll = self.CreateDial("Max Value", -1, 1, 1)
        self.maxValue_controll.edit.textChanged.connect(self.min_max_refresh)

        self.dials.addLayout(self.gain_controll.layout)
        self.dials.addLayout(self.minValue_controll.layout)
        self.dials.addLayout(self.maxValue_controll.layout)


    def gain_edit_changed_value(self):
        self.SetValue(self.gain_controll, self.cpplib.Overdrive_SetGain)


    def min_max_refresh(self):
        try:
            minValue = float(self.minValue_controll.edit.text())
            maxValue = float(self.maxValue_controll.edit.text())
        except ValueError:
            return

        self.cpplib.Overdrive_SetMinMaxValue(self.effectPtr, minValue, maxValue)
        self.draw_plot()


    def algorithm_combo_changed(self):
        self.cpplib.Effect_SetAlgorithm(self.effectPtr, self.algorithm_combo.currentIndex())
        self.draw_plot()

        self.SetDialEnabled(self.gain_controll, self.cpplib.Overdrive_IsUsingGain(self.effectPtr))
        self.SetDialEnabled(self.minValue_controll, self.cpplib.Overdrive_IsUsingMinValue(self.effectPtr))
        self.SetDialEnabled(self.maxValue_controll, self.cpplib.Overdrive_IsUsingMaxValue(self.effectPtr))
