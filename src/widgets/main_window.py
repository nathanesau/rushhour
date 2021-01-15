from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from .main_widget import MainWidget

class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)

        # widgets
        self.mainWidget = MainWidget(self)
        self.statusLabel = QLabel(self)

        self.setCentralWidget(self.mainWidget)
        self.resize(700, 450)
        self.setWindowTitle("Rush Hour")
        self.setWindowIcon(QIcon(":icon.png"))
        self.setStatus("Loaded App")
        self.setFixedSize(700, 450)
    
    def setStatus(self, status):
        self.statusBar().showMessage(str(status))
