from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *


class SquareWidget(QLabel):
    def __init__(self, row, col, parent=None):
        super().__init__(parent)
        self.row = row
        self.col = col
        self.setAlignment(Qt.AlignCenter)
        self.setFont(QFont("Times", 36))
        self.setStyleSheet("border: 3px solid black;")

    def updateAlpha(self, alpha):
        style = self.styleSheet()
        background = [e for e in style.split(';') if 'background' in e][0]
        rgba = background.split(':')[1].strip()
        r, g, b, a = rgba.replace('rgba', '').replace('(', '').replace(')', '').split(', ') 
        style = style.replace(background, background.replace(rgba, f'rgba({r}, {g}, {b}, {alpha})'))
        #self.setStyleSheet(f"{style}; color: green;")
        self.setStyleSheet(style)

    def mousePressEvent(self, event):
        if self.text() != '.':
            self.parent().onSquareClicked(self)