import sys
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from widgets.main_window import MainWindow

app = QApplication(sys.argv)

mainWindow = MainWindow()
mainWindow.show()

app.exec()