import sys

from PyQt6.QtWidgets import QLabel, QComboBox

sys.path.append("..")
from Effect import Effect


class ModulationTab(Effect):
    def __init__(self, effectPtr, cpplib):
        Effect.__init__(self, effectPtr, cpplib)

        self.SetEffectSettings()
        self.SetDials()
        self.delay_edit_changed_value()

        self.algorithm_combo_changed()

    def SetEffectSettings(self):
        self.algorithm_combo = QComboBox()

        algorithms = []
        for alg_id in range(self.cpplib.Effect_GetAlgorithmsNo(self.effectPtr)):
            algorithms.append(self.cpplib.Effect_GetAlgorithmName(self.effectPtr, alg_id))
        self.algorithm_combo.addItems(algorithms)
        self.algorithm_combo.currentTextChanged.connect(self.algorithm_combo_changed)

        self.lfo_combo = QComboBox()
        lfos = []
        for lfo_id in range(self.cpplib.Modulation_GetLFOsNo(self.effectPtr)):
            lfos.append(self.cpplib.Modulation_GetLFOName(self.effectPtr, lfo_id))
        self.lfo_combo.addItems(lfos)
        self.lfo_combo.currentTextChanged.connect(self.lfo_combo_changed)


        self.SetEffectLayout()


    def SetEffectLayout(self):
        self.effect_settings.addWidget(QLabel("Algorithm:"))
        self.effect_settings.addWidget(self.algorithm_combo)
        self.effect_settings.addWidget(QLabel("LFO signal:"))
        self.effect_settings.addWidget(self.lfo_combo)


    def SetDials(self):
        self.delay_controll = self.CreateDial("Delay", 0, 0.1, 0.01, multiplier=10000)
        self.delay_controll.edit.textChanged.connect(self.delay_edit_changed_value)

        self.depth_controll = self.CreateDial("Depth", 0, 1, 0.5, multiplier=1000)
        self.depth_controll.edit.textChanged.connect(self.depth_edit_changed_value)

        self.alpha_controll = self.CreateDial("Alpha", 0, 1, 0.5)
        self.alpha_controll.edit.textChanged.connect(self.alpha_edit_changed_value)

        self.feedback_controll = self.CreateDial("Feedback", 0, 1, 0.5)
        self.feedback_controll.edit.textChanged.connect(self.feedback_edit_changed_value)

        self.lfoFreq_controll = self.CreateDial("LFO Freq", 0, 20, 1, multiplier=100)
        self.lfoFreq_controll.edit.textChanged.connect(self.lfoFreq_edit_changed_value)

        self.dials.addLayout(self.delay_controll.layout)
        self.dials.addLayout(self.depth_controll.layout)
        self.dials.addLayout(self.alpha_controll.layout)
        self.dials.addLayout(self.feedback_controll.layout)
        self.dials.addLayout(self.lfoFreq_controll.layout)


    def delay_edit_changed_value(self):
        self.SetValue(self.delay_controll, self.cpplib.Modulation_SetDelay, multiplier=1000)


    def alpha_edit_changed_value(self):
        self.SetValue(self.alpha_controll, self.cpplib.Modulation_SetAlpha)


    def depth_edit_changed_value(self):
        self.SetValue(self.depth_controll, self.cpplib.Modulation_SetDepth)


    def lfoFreq_edit_changed_value(self):
        self.SetValue(self.lfoFreq_controll, self.cpplib.Modulation_SetLFOFrequency)


    def feedback_edit_changed_value(self):
        self.SetValue(self.feedback_controll, self.cpplib.Modulation_SetFeedback)


    def lfo_combo_changed(self):
        self.cpplib.Modulation_SetLFO(self.effectPtr, self.lfo_combo.currentIndex())
        self.draw_plot()


    def algorithm_combo_changed(self):
        self.cpplib.Effect_SetAlgorithm(self.effectPtr, self.algorithm_combo.currentIndex())
        self.draw_plot()

        self.SetDialEnabled(self.delay_controll, self.cpplib.Modulation_IsUsingDelay(self.effectPtr))
        self.SetDialEnabled(self.alpha_controll, self.cpplib.Modulation_IsUsingAlpha(self.effectPtr))
        self.SetDialEnabled(self.feedback_controll, self.cpplib.Modulation_IsUsingFeedback(self.effectPtr))
        self.SetDialEnabled(self.depth_controll, self.cpplib.Modulation_IsUsingDepth(self.effectPtr))
        self.SetDialEnabled(self.lfoFreq_controll, self.cpplib.Modulation_IsUsingLFOFrequency(self.effectPtr))
