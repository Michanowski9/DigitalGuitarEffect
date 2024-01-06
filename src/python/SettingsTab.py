from PyQt6.QtWidgets import QComboBox, QGridLayout, QLabel, QWidget

class SettingsTab(QWidget):
    def __init__(self, cpplib):
        QWidget.__init__(self)

        # cpp lib wrapper
        self.cpplib = cpplib

        # gui
        self.SetShortcuts()
        self.SetComboBoxes()
        self.SetLayout()

        # update comboBoxes
        self.inputOutputDevice_combobox_changed()

        self.show()


    def SetShortcuts(self):
        pass


    def SetComboBoxes(self):
        self.input_device_label = QLabel("Input Device")
        self.input_device_comboBox = QComboBox()
        self.input_device_comboBox.clear()
        self.input_device_comboBox.addItems(self.cpplib.GetInputDevices().values())

        self.output_device_label = QLabel("Output Device")
        self.output_device_comboBox = QComboBox()
        self.output_device_comboBox.clear()
        self.output_device_comboBox.addItems(self.cpplib.GetOutputDevices().values())

        self.input_device_comboBox.currentTextChanged.connect(self.inputOutputDevice_combobox_changed)
        self.output_device_comboBox.currentTextChanged.connect(self.inputOutputDevice_combobox_changed)

        self.sample_rates_label = QLabel("Sample Rates")
        self.sample_rates_comboBox = QComboBox()

        # latency
        self.input_device_latency_label = QLabel("Input Latency [ms]")
        self.input_device_low_latency_value = QLabel("")
        self.input_device_high_latency_value = QLabel("")

        self.output_device_latency_label = QLabel("Output Latency [ms]")
        self.output_device_low_latency_value = QLabel("")
        self.output_device_high_latency_value = QLabel("")


    def SetLayout(self):
        layout = QGridLayout()
        layout.addWidget(self.input_device_label, 0, 0)
        layout.addWidget(self.input_device_comboBox, 0, 1)

        layout.addWidget(self.input_device_latency_label, 1, 0)
        layout.addWidget(self.input_device_low_latency_value, 1, 1)
        layout.addWidget(self.input_device_high_latency_value, 1, 2)

        layout.addWidget(self.output_device_label, 2, 0)
        layout.addWidget(self.output_device_comboBox, 2, 1)

        layout.addWidget(self.output_device_latency_label, 3, 0)
        layout.addWidget(self.output_device_low_latency_value, 3, 1)
        layout.addWidget(self.output_device_high_latency_value, 3, 2)

        layout.addWidget(self.sample_rates_label, 4, 0)
        layout.addWidget(self.sample_rates_comboBox, 4, 1)

        self.setLayout(layout)


    def inputOutputDevice_combobox_changed(self):
        try:
            inputIndex = list(self.cpplib.GetInputDevices().keys())[self.input_device_comboBox.currentIndex()]
            outputIndex = list(self.cpplib.GetOutputDevices().keys())[self.output_device_comboBox.currentIndex()]
        except:
            return

        self.sample_rates_comboBox.clear()
        self.sample_rates_comboBox.addItems([str(x) for x in self.cpplib.GetSampleRates(inputIndex, outputIndex)])

        self.input_device_low_latency_value.setText(str(1000 * self.cpplib.GetInputLowLatency(inputIndex)))
        self.input_device_high_latency_value.setText(str(1000 * self.cpplib.GetInputHighLatency(inputIndex)))

        self.output_device_low_latency_value.setText(str(1000 * self.cpplib.GetOutputLowLatency(outputIndex)))
        self.output_device_high_latency_value.setText(str(1000 * self.cpplib.GetOutputHighLatency(outputIndex)))


    def GetInputIndex(self):
        return list(self.cpplib.GetInputDevices().keys())[self.input_device_comboBox.currentIndex()]

    def GetOutputIndex(self):
        return list(self.cpplib.GetOutputDevices().keys())[self.output_device_comboBox.currentIndex()]

    def GetSampleRates(self):
        try:
            result = int(self.sample_rates_comboBox.currentText())
        except:
            result = -1
        return result


