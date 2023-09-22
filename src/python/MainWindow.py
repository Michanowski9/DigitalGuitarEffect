from PyQt6.QtWidgets import QComboBox, QGridLayout, QLabel, QWidget, QPushButton


class MainWindow(QWidget):
    def __init__(self):
        QWidget.__init__(self)

        # main window settings
        self.setWindowTitle("Digital Guitar Effect - M. Soja, A. Sałata 2023")
        self.resize(1000,1000)
        
        # gui
        self.SetShortcuts()
        self.SetComboBoxes()
        self.SetButtons()
        self.SetLayout()

        self.show()


    def SetShortcuts(self):
        pass


    def SetComboBoxes(self):
        self.input_device_label = QLabel("Input Device")
        self.input_device = QComboBox()

        self.output_device_label = QLabel("Output Device")
        self.output_device = QComboBox()

        self.sample_rates_label = QLabel("Sample Rates")
        self.sample_rates = QComboBox()


    def SetButtons(self):
        self.start_button = self.MakeButton('Start', self.start_button_on_click)
        self.stop_button = self.MakeButton('Stop', self.stop_button_on_click)


    def SetLayout(self):
        mainLayout = QGridLayout()

        mainLayout.addWidget(self.input_device_label, 0, 0)
        mainLayout.addWidget(self.input_device, 0, 1)

        mainLayout.addWidget(self.output_device_label, 1, 0)
        mainLayout.addWidget(self.output_device, 1, 1)

        mainLayout.addWidget(self.sample_rates_label, 2, 0)
        mainLayout.addWidget(self.sample_rates, 2, 1)


        mainLayout.addWidget(self.start_button, 10, 0)
        mainLayout.addWidget(self.stop_button, 10, 1)

        self.setLayout(mainLayout)

    def MakeButton(self, text, func):
        result = QPushButton(text, self)
        result.clicked.connect(func)
        return result


    def start_button_on_click(self):
        pass


    def stop_button_on_click(self):
        pass


