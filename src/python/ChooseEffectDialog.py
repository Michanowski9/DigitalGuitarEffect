from PyQt6.QtWidgets import QDialog, QVBoxLayout, QPushButton

class ChooseEffectDialog(QDialog):
    def __init__(self, effects, parent=None):
        super().__init__(parent)

        self.result = None

        self.setWindowTitle("Choose effect to add")
        self.resize(300, 100)

        self.layout = QVBoxLayout()

        for effect in effects:
            self.CreateButton(effect)

        self.setLayout(self.layout)

    def CreateButton(self, text):
        def on_click():
            self.result = text
            self.accept()

        effect_button = QPushButton(text, self)
        effect_button.clicked.connect(on_click)
        self.layout.addWidget(effect_button)
