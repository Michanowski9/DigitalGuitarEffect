from PyQt6.QtWidgets import QWidget, QVBoxLayout, QPushButton

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
        self.SetLayout()

        self.draw_plot()
        self.isOn = False

    def SetButtons(self):
        self.on_off_button = self.MakeButton('On/Off', self.on_off_button_on_click)


    def SetLayout(self):
        mainLayout = QVBoxLayout()
        #mainLayout.addWidget(QLabel("Overdrive [" + str(self.effectID) + "]"))
        mainLayout.addWidget(self.on_off_button)
        mainLayout.addWidget(self.canvas)

        self.setLayout(mainLayout)


    def MakeButton(self, text, func):
        result = QPushButton(text, self)
        result.clicked.connect(func)
        return result


    def draw_plot(self):
        x = [math.sin(x/100.0*4*math.pi) for x in range(0,100)]
        y = [math.sin(x/100.0*4*math.pi) for x in range(0,100)]

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

