import sys

from PyQt6.QtWidgets import QLabel, QComboBox

sys.path.append("..")
from Effect import Effect

class DelayTab(Effect):
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

        self.SetEffectLayout()


    def SetEffectLayout(self):
        self.effect_settings.addWidget(QLabel("Algorithm:"))
        self.effect_settings.addWidget(self.algorithm_combo)


    def SetDials(self):
        self.delay_controll = self.CreateDial("Delay", 0, 5, 0.1, multiplier=1000)
        self.delay_controll.edit.textChanged.connect(self.delay_edit_changed_value)

        self.alpha_controll = self.CreateDial("Alpha", 0, 1, 0.5)
        self.alpha_controll.edit.textChanged.connect(self.alpha_edit_changed_value)

        self.feedback_controll = self.CreateDial("Feedback", 0, 1, 0.5)
        self.feedback_controll.edit.textChanged.connect(self.feedback_edit_changed_value)

        self.leftInputVolume_controll = self.CreateDial("Left Input Volume", 0, 1, 1)
        self.leftInputVolume_controll.edit.textChanged.connect(self.leftInputVolume_edit_changed_value)

        self.rightInputVolume_controll = self.CreateDial("Right Input Volume", 0, 1, 0)
        self.rightInputVolume_controll.edit.textChanged.connect(self.rightInputVolume_edit_changed_value)


        self.dials.addLayout(self.delay_controll.layout)
        self.dials.addLayout(self.alpha_controll.layout)
        self.dials.addLayout(self.feedback_controll.layout)
        self.dials.addLayout(self.leftInputVolume_controll.layout)
        self.dials.addLayout(self.rightInputVolume_controll.layout)


    def delay_edit_changed_value(self):
        self.SetValue(self.delay_controll, self.cpplib.Delay_SetDelay, multiplier=1000)


    def alpha_edit_changed_value(self):
        self.SetValue(self.alpha_controll, self.cpplib.Delay_SetAlpha)


    def feedback_edit_changed_value(self):
        self.SetValue(self.feedback_controll, self.cpplib.Delay_SetFeedback)

    def leftInputVolume_edit_changed_value(self):
        self.SetValue(self.leftInputVolume_controll, self.cpplib.Delay_SetLeftInputVolume)


    def rightInputVolume_edit_changed_value(self):
        self.SetValue(self.rightInputVolume_controll, self.cpplib.Delay_SetRightInputVolume)



    def algorithm_combo_changed(self):
        self.cpplib.Effect_SetAlgorithm(self.effectPtr, self.algorithm_combo.currentIndex())
        self.draw_plot()

        self.SetDialEnabled(self.delay_controll, self.cpplib.Delay_IsUsingDelay(self.effectPtr))
        self.SetDialEnabled(self.alpha_controll, self.cpplib.Delay_IsUsingAlpha(self.effectPtr))
        self.SetDialEnabled(self.feedback_controll, self.cpplib.Delay_IsUsingFeedback(self.effectPtr))
        self.SetDialEnabled(self.leftInputVolume_controll, self.cpplib.Delay_IsUsingLeftInputVolume(self.effectPtr))
        self.SetDialEnabled(self.rightInputVolume_controll, self.cpplib.Delay_IsUsingRightInputVolume(self.effectPtr))
