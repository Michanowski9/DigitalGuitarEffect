from PyQt6.QtWidgets import QApplication, QDialog, QVBoxLayout, QPushButton
from PyQt6.QtCore import Qt

class ChooseEffectDialog(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)

        self.result = None

        self.setWindowTitle("Choose effect to add")
        self.resize(300, 100)

        layout = QVBoxLayout()

        overdrive_button = QPushButton("Overdrive", self)
        overdrive_button.clicked.connect(self.on_overdrive_clicked)
        layout.addWidget(overdrive_button)

        delay_button = QPushButton("Delay", self)
        delay_button.clicked.connect(self.on_delay_clicked)
        layout.addWidget(delay_button)

        chorus_button = QPushButton("Chorus", self)
        chorus_button.clicked.connect(self.on_chorus_clicked)
        layout.addWidget(chorus_button)

        self.setLayout(layout)

    def on_overdrive_clicked(self):
        self.result = "Overdrive"
        self.accept()

    def on_delay_clicked(self):
        self.result = "Delay"
        self.accept()

    def on_chorus_clicked(self):
        self.result = "Chorus"
        self.accept()
