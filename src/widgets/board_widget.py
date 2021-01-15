from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
import copy
from .square_widget import SquareWidget

# controllers
import os
import sys
sys.path.append('{}/../'.format(os.path.dirname(os.path.abspath(__file__))))
from controllers.rush_hour import RushHour


class BoardWidget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)

        # data
        self.carSelected = None

        # widgets
        self.squares = [[SquareWidget(i, j) for j in range(6)] for i in range(6)]

        # layouts
        self.gridLayout = QGridLayout()
        self.gridLayout.setSpacing(0)

        for i in range(6):
            for j in range(6):
                self.gridLayout.addWidget(self.squares[i][j], i, j)
        
        self.mainLayout = QVBoxLayout()
        self.mainLayout.addWidget(QLabel("Use arrow keys to move cars"))
        self.mainLayout.addLayout(self.gridLayout)

        self.setLayout(self.mainLayout)

    def renderLevel(self, level, cars):
        # clear selection
        self.carSelected = None

        for i in range(6):
            for j in range(6):
                self.squares[i][j].setText(level[i][j])
                if level[i][j] in cars:
                    car = cars[level[i][j]]
                    style = f'background: {car["color"]}; border: 3px solid black;'
                    self.squares[i][j].setStyleSheet(style)
                else:
                    self.squares[i][j].setStyleSheet("border: 3px solid black;")

    def onSquareClicked(self, square):
        self.parent().onSquareClicked(square)

    def selectCar(self, car):
        if self.carSelected:
            # unselect previous car
            for square in self.carSelected["squares"]:
                self.squares[square[0]][square[1]].updateAlpha(255)
        
        # select new car
        for square in car["squares"]:
            self.squares[square[0]][square[1]].updateAlpha(50)
        
        self.carSelected = car

    def moveSelectedCar(self, board, key):
        """
        board: [['.', '.', 'A', 'A', '.', '.'], ...]
        key: 'Up', 'Down', 'Left' or 'Right'
        """
        init_board = copy.deepcopy(board)

        controller = RushHour(board)
        carName = self.carSelected["name"]
        dir = RushHour.UP if key == 'Up' \
            else RushHour.DOWN if key == 'Down' \
            else RushHour.LEFT if key == 'Left' \
            else RushHour.RIGHT if key == 'Right' \
            else None
        controller.make_move(carName, dir, length=1)

        return init_board != board

