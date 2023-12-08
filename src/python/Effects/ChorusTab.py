import sys

from PyQt6.QtWidgets import QLabel, QComboBox

sys.path.append("..")
from Effect import Effect

class ChorusTab(Effect):
    def __init__(self, effectPtr, cpplib):
        Effect.__init__(self, effectPtr, cpplib)

        self.SetEffectSettings()
        self.SetDials()
        self.delay_edit_changed_value()


    def SetEffectSettings(self):
        self.algorithm_combo = QComboBox()

        algorithms = []
        for alg_id in range(self.cpplib.Effect_GetAlgorithmsNo(self.effectPtr)):
            algorithms.append(self.cpplib.Effect_GetAlgorithmName(self.effectPtr, alg_id))
        self.algorithm_combo.addItems(algorithms)
        self.algorithm_combo.currentTextChanged.connect(self.algorithm_combo_changed)

        self.SetEffectLayout()


    def SetEffectLayout(self):
        self.effect_settings.addWidget(QLabel("Algorithm"))
        self.effect_settings.addWidget(self.algorithm_combo)


    def SetDials(self):
        _, _, self.delay_edit, delay_layout = self.CreateDial("Delay", 0, 1, 0.01, multiplier=10000)
        self.delay_edit.textChanged.connect(self.delay_edit_changed_value)

        _, _, self.alpha_edit, alpha_layout = self.CreateDial("Alpha", 0, 1, 0.5)
        self.alpha_edit.textChanged.connect(self.alpha_edit_changed_value)

        _, _, self.depth_edit, depth_layout = self.CreateDial("Depth", 0, 1, 0.1, multiplier=1000)
        self.depth_edit.textChanged.connect(self.depth_edit_changed_value)

        _, _, self.lfoFreq_edit, lfoFreq_layout = self.CreateDial("LFO Freq", 0, 20, 1, multiplier=100)
        self.lfoFreq_edit.textChanged.connect(self.lfoFreq_edit_changed_value)

        self.dials.addLayout(delay_layout)
        self.dials.addLayout(alpha_layout)
        self.dials.addLayout(depth_layout)
        self.dials.addLayout(lfoFreq_layout)


    def delay_edit_changed_value(self):
        try:
            delay = float(self.delay_edit.text())
        except ValueError:
            return

        self.cpplib.Chorus_SetDelay(self.effectPtr, delay * 1000)
        self.draw_plot()


    def alpha_edit_changed_value(self):
        try:
            alpha = float(self.alpha_edit.text())
        except ValueError:
            return

        self.cpplib.Chorus_SetAlpha(self.effectPtr, alpha)
        self.draw_plot()


    def depth_edit_changed_value(self):
        try:
            depth = float(self.depth_edit.text())
        except ValueError:
            return

        self.cpplib.Chorus_SetDepth(self.effectPtr, depth)
        self.draw_plot()


    def lfoFreq_edit_changed_value(self):
        try:
            lfoFreq = float(self.lfoFreq_edit.text())
        except ValueError:
            return

        self.cpplib.Chorus_SetLFOFrequency(self.effectPtr, lfoFreq)
        self.draw_plot()


    def algorithm_combo_changed(self):
        self.cpplib.Effect_SetAlgorithm(self.effectPtr, self.algorithm_combo.currentIndex())
        self.draw_plot()
