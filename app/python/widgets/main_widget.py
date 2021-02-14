from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from .level_widget import LevelWidget
from .board_widget import BoardWidget
from datetime import datetime

# controllers
import os
import sys
sys.path.append('{}/../'.format(os.path.dirname(os.path.abspath(__file__))))
from controllers.rush_hour import RushHour


DEFAULT_LEVEL_TEXT = (
    "..AA..\n"
    ".XX.B.\n"
    "....B.\n"
    ".DCCC.\n"
    ".D....\n"
    ".EE...\n"
)


class MainWidget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)

        # widgets
        self.levelWidget = LevelWidget(self)
        level = [list(line) for line in DEFAULT_LEVEL_TEXT.splitlines() if line.strip()]
        self.levelWidget.setOriginalLevel(level)
        self.boardWidget = BoardWidget(self)
        self.boardWidget.renderLevel(self.levelWidget.level,
                                     self.levelWidget.cars)

        # event handlers
        self.levelWidget.editBtn.clicked.connect(self.onEditBtn)
        self.levelWidget.applyBtn.clicked.connect(self.onApplyBtn)

        # layouts
        self.levelLayout = QHBoxLayout()
        self.levelLayout.addWidget(self.levelWidget)
        self.boardLayout = QHBoxLayout()
        self.boardLayout.addWidget(self.boardWidget)
        self.mainLayout = QHBoxLayout()
        self.mainLayout.addLayout(self.levelLayout, 40)
        self.mainLayout.addLayout(self.boardLayout, 60)

        self.setLayout(self.mainLayout)
        
    def onEditBtn(self):
        # make board editable
        self.levelWidget.originalBoardTE.setReadOnly(False)
        self.levelWidget.originalBoardTE.setStyleSheet("")

    def onApplyBtn(self):
        # disable editing
        self.levelWidget.originalBoardTE.setReadOnly(True)
        self.levelWidget.originalBoardTE.setStyleSheet("background: lightgrey")

        levelText = self.levelWidget.originalBoardTE.toPlainText()
        valid = self.levelWidget._validate_level(levelText)

        if valid:  # update board
            level = [list(line) for line in levelText.splitlines() if line.strip()]
            self.levelWidget.setOriginalLevel(level)
            self.levelWidget._parse_level(level)
            self.boardWidget.renderLevel(self.levelWidget.level,
                                         self.levelWidget.cars)
            status = f'Board Change Detected at {datetime.utcnow().strftime(("%m/%d/%Y, %H:%M:%S"))}'
            self.parent().setStatus(status)
        else:
            status = (f'Invalid Board Change Detected at '
                      f'{datetime.utcnow().strftime(("%m/%d/%Y, %H:%M:%S"))} '
                      f'(board change not applied)')
            self.parent().setStatus(status)

    def onSquareClicked(self, square):
        # check to see if level editing is currently on
        if not self.levelWidget.originalBoardTE.isReadOnly():
            return

        i, j = square.row, square.col
        car = self.levelWidget.cars[self.levelWidget.level[i][j]]
        self.boardWidget.selectCar(car)
        status = f'Selected Car {self.levelWidget.level[i][j]}'
        self.parent().setStatus(status)

    def keyReleaseEvent(self, event):
        # check to see if level editing is currently on
        if not self.levelWidget.originalBoardTE.isReadOnly():
            return

        # check if a car is currently selected
        if not self.boardWidget.carSelected:
            return

        # the car we are trying to move
        carName = self.boardWidget.carSelected["name"]

        if event.key() == Qt.Key_Up:  # up
            if self.boardWidget.moveSelectedCar(self.levelWidget.level, 'Up'):
                self.levelWidget.setCurrentLevel(self.levelWidget.level)
                self.boardWidget.renderLevel(self.levelWidget.level, self.levelWidget.cars)
                self.boardWidget.carSelected = self.levelWidget.cars[carName]
                status = f'Moved Car {self.boardWidget.carSelected["name"]} Up'
                self.parent().setStatus(status)
        elif event.key() == Qt.Key_Down:  # down
            if self.boardWidget.moveSelectedCar(self.levelWidget.level, 'Down'):
                self.levelWidget.setCurrentLevel(self.levelWidget.level)
                self.boardWidget.renderLevel(self.levelWidget.level, self.levelWidget.cars)
                self.boardWidget.carSelected = self.levelWidget.cars[carName]
                status = f'Moved Car {self.boardWidget.carSelected["name"]} Down'
                self.parent().setStatus(status)
        elif event.key() == Qt.Key_Left:  # left
            if self.boardWidget.moveSelectedCar(self.levelWidget.level, 'Left'):
                self.levelWidget.setCurrentLevel(self.levelWidget.level)
                self.boardWidget.renderLevel(self.levelWidget.level, self.levelWidget.cars)
                self.boardWidget.carSelected = self.levelWidget.cars[carName]
                status = f'Moved Car {self.boardWidget.carSelected["name"]} Left'
                self.parent().setStatus(status)
        elif event.key() == Qt.Key_Right:  # right
            if self.boardWidget.moveSelectedCar(self.levelWidget.level, 'Right'):
                self.levelWidget.setCurrentLevel(self.levelWidget.level)
                self.boardWidget.renderLevel(self.levelWidget.level, self.levelWidget.cars)
                self.boardWidget.carSelected = self.levelWidget.cars[carName]
                status = f'Moved Car {self.boardWidget.carSelected["name"]} Right'
                self.parent().setStatus(status)

        controller = RushHour(self.levelWidget.level)
        if controller.is_solved():
            msgBox = QMessageBox()
            msgBox.setWindowTitle("Notification")
            msgBox.setText("Congrats! You have solved the Rush Hour Puzzle!")
            msgBox.exec()