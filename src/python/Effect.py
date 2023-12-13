from PyQt6.QtWidgets import QWidget, QHBoxLayout, QVBoxLayout, QComboBox, QPushButton, QDial, QLabel, QLineEdit
from PyQt6.QtCore import Qt

import matplotlib.pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg
import math

class PropertyControll:
    def __init__(self, label, dial, edit, layout):
        self.label = label
        self.dial = dial
        self.edit = edit
        self.layout = layout


class Effect(QWidget):
    def __init__(self, effectPtr, cpplib):
        QWidget.__init__(self)

        self.effectPtr = effectPtr
        self.cpplib = cpplib

        self.SetPlotWindow()
        self.SetButtons()
        self.SetLayout()

        self.draw_plot()
        self.isOn = False


    def SetPlotWindow(self):
        # creating plot
        self.figure = plt.figure()
        self.canvas = FigureCanvasQTAgg(self.figure)

        self.visualizationInput_combo = QComboBox()
        self.visualizationInput_combo.addItems(["sin", "impulse", "tone 5Hz", "tone 20Hz"])
        self.visualizationInput_combo.currentTextChanged.connect(self.visualizationInput_combo_changed)


    def SetLayout(self):
        mainLayout = QVBoxLayout()

        self.dials = QHBoxLayout()
        self.effect_settings = QVBoxLayout()

        mainLayout.addWidget(self.on_off_button)
        mainLayout.addLayout(self.effect_settings)
        mainLayout.addLayout(self.dials)
        mainLayout.addWidget(self.canvas)
        mainLayout.addWidget(self.visualizationInput_combo)

        self.setLayout(mainLayout)


    def SetButtons(self):
        self.on_off_button = self.MakeButton('On/Off', self.on_off_button_on_click)

    def RemoveEffect(self):
        self.cpplib.RemoveEffect(self.effectPtr)

    def MakeButton(self, text, func):
        result = QPushButton(text, self)
        result.clicked.connect(func)
        return result


    def CreateDial(self, label, minValue, maxValue, value, multiplier=100):
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

        if multiplier == 1:
            result_dial.valueChanged.connect(lambda: result_edit.setText(str(int(result_dial.value()))))
        else:
            result_dial.valueChanged.connect(lambda: result_edit.setText(str(result_dial.value() / multiplier)))
        result_edit.textChanged.connect(refresh_dial)

        result_dial.setMinimum(int(minValue * multiplier))
        result_dial.setMaximum(int(maxValue * multiplier))
        result_dial.setValue(int(value * multiplier))
        if value == 0:
            result_edit.setText("0")

        result_layout = QVBoxLayout()
        result_layout.addWidget(result_label)
        result_layout.addWidget(result_dial)
        result_layout.addWidget(result_edit)

        return PropertyControll(result_label, result_dial, result_edit, result_layout)



    def SetValue(self, controll, setter, multiplier=1, valType=float):
        try:
            val = valType(controll.edit.text())
        except ValueError:
            print("failed to set")
            return

        setter(self.effectPtr, val * multiplier)
        self.draw_plot()

    def SetDialEnabled(self, controll, value):
        controll.dial.setEnabled(value)
        controll.edit.setEnabled(value)

    def draw_plot(self):
        x = []
        yLeft = []
        yRight = []
        time = 5 # sec
        sampling = 1000 # in 1 sec

        if self.visualizationInput_combo.currentIndex() == 1:
            x = [0 for _ in range(0, sampling * time)]
            for i in range(0, len(x)):
                if i <= 10:
                    x[i] = i * 0.1
                elif i <= 20:
                    x[i] = 1 - 0.5 * i * 0.1
                else:
                    break
        elif self.visualizationInput_combo.currentIndex() == 2:
            x = self.GetDampingSin(hz=5, damping_coefficient=5, time=time, sampling=sampling)
        elif self.visualizationInput_combo.currentIndex() == 3:
            x = self.GetDampingSin(hz=20, damping_coefficient=5, time=time, sampling=sampling)
        else:
            periods_no = 2
            x = [math.sin(x / float(sampling * time) * periods_no * 2 * math.pi) for x in range(0, sampling * time)]

        y1 = [0 for _ in range(sampling * time)]
        y2 = [y for y in x]
        yLeft = y1 + y2
        yRight = [y for y in yLeft]

        self.cpplib.CalculateExampleData(self.effectPtr, yLeft, yRight)

        yLeft = yLeft[(sampling * time):]
        yRight = yRight[(sampling * time):]

        self.figure.clear()

        ax = self.figure.add_subplot(111)
        ax.plot(x, color="r", alpha=0.2)
        legend = ['input']
        if self.CheckIfEquals(yLeft, yRight):
            legend.append('output')
        else:
            legend.append('output R')
            legend.append('output L')
            ax.plot(yRight, color="g")

        ax.plot(yLeft, color="b")
        ax.set_ylim([-1.05,1.05])
        ax.legend(legend, loc=1)

        self.canvas.draw()

    def CheckIfEquals(self, a, b):
        for i in range(len(a)):
            if a[i] != b[i]:
                return False
        return True

    def GetDampingSin(self, hz, damping_coefficient, time, sampling):
        periods_no = time * hz
        probes_no = sampling * time
        return [math.sin(x / float(probes_no) * periods_no * 2 * math.pi) * (math.e / math.exp(1 + damping_coefficient * x / float(probes_no))) for x in range(0, probes_no)]

    def on_off_button_on_click(self):
        self.isOn = not self.isOn
        if self.isOn:
            self.on_off_button.setStyleSheet("background-color: #00ff00")
        else:
            self.on_off_button.setStyleSheet("background-color: light gray")
        self.cpplib.SetEffectOn(self.effectPtr, self.isOn);
        self.draw_plot()

    def visualizationInput_combo_changed(self):
        self.draw_plot()
