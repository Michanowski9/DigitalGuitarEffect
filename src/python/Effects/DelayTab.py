import sys

sys.path.append("..")
from Effect import Effect

class DelayTab(Effect):
    def __init__(self, effectPtr, cpplib):
        Effect.__init__(self, effectPtr, cpplib)

        self.SetDials()

        self.delay_edit_changed_value()


    def SetDials(self):
        _, _, self.delay_edit, delay_layout = self.CreateDial("Delay", 0, 5, 0.1, multiplier=1000)
        self.delay_edit.textChanged.connect(self.delay_edit_changed_value)

        _, _, self.alpha_edit, alpha_layout = self.CreateDial("Alpha", 0, 1, 0.5)
        self.alpha_edit.textChanged.connect(self.alpha_edit_changed_value)

        self.dials.addLayout(delay_layout)
        self.dials.addLayout(alpha_layout)


    def delay_edit_changed_value(self):
        try:
            delay = float(self.delay_edit.text())
        except ValueError:
            return

        self.cpplib.Delay_SetDelay(self.effectPtr, delay * 1000)
        self.draw_plot()


    def alpha_edit_changed_value(self):
        try:
            alpha = float(self.alpha_edit.text())
        except ValueError:
            return

        self.cpplib.Delay_SetAlpha(self.effectPtr, alpha)
        self.draw_plot()

