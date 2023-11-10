from PyQt6.QtWidgets import QWidget, QVBoxLayout, QPushButton, QDial, QLabel, QLineEdit
from PyQt6.QtCore import Qt

import matplotlib.pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg
import math


class Effect(QWidget):
    def __init__(self, effectPtr, cpplib):
        QWidget.__init__(self)

        self.effectPtr = effectPtr
        self.cpplib = cpplib

        # creating plot
        self.figure = plt.figure()
        self.canvas = FigureCanvasQTAgg(self.figure)

        self.SetButtons()

        self.draw_plot()
        self.isOn = False


    def SetButtons(self):
        self.on_off_button = self.MakeButton('On/Off', self.on_off_button_on_click)

    def RemoveEffect(self):
        self.cpplib.RemoveEffect(self.effectPtr)

    def MakeButton(self, text, func):
        result = QPushButton(text, self)
        result.clicked.connect(func)
        return result


    def CreateDial(self, label, minValue, maxValue, value):
        multiplier = 100

        result_label = QLabel(label, alignment=Qt.AlignmentFlag.AlignCenter)

        result_dial = QDial()
        result_dial.setNotchesVisible(False)

        result_edit = QLineEdit(alignment=Qt.AlignmentFlag.AlignCenter)

        # connections
        def refresh_dial():
            result_edit.setText(result_edit.text().replace(",", "."))
            try:
                result_edit_new_value = float(result_edit.text())
            except ValueError:
                return
            result_dial.setValue(int(result_edit_new_value*multiplier))

        result_dial.valueChanged.connect(lambda: result_edit.setText(str(result_dial.value() / multiplier)))
        result_edit.textChanged.connect(refresh_dial)

        result_dial.setMinimum(minValue * multiplier)
        result_dial.setMaximum(maxValue * multiplier)
        result_dial.setValue(int(value * multiplier))

        result_layout = QVBoxLayout()
        result_layout.addWidget(result_label)
        result_layout.addWidget(result_dial)
        result_layout.addWidget(result_edit)

        return result_label, result_dial, result_edit, result_layout


    def draw_plot(self):
        x = [math.sin(x/1000.0*4*math.pi) for x in range(0,1000)]
        y = [math.sin(x/1000.0*4*math.pi) for x in range(0,1000)]

        self.cpplib.CalculateExampleData(self.effectPtr, y)
        self.figure.clear()

        ax = self.figure.add_subplot(111)
        ax.plot(x, color="r", alpha=0.2)
        ax.plot(y, color="b")
        ax.legend(['input', 'output'], loc=1)

        self.canvas.draw()


    def on_off_button_on_click(self):
        self.isOn = not self.isOn
        if self.isOn:
            self.on_off_button.setStyleSheet("background-color: #00ff00")
        else:
            self.on_off_button.setStyleSheet("background-color: light gray")
        self.cpplib.SetEffectOn(self.effectPtr, self.isOn);
        self.draw_plot()

