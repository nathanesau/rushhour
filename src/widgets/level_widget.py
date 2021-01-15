from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *


COLORS = [    
    'rgba(0, 128, 0, 255)', # 'green',
    'rgba(0, 0, 255, 255)', # 'blue',
    'rgba(0, 255, 255, 255)', # 'cyan',
    'rgba(255, 255, 0, 255)', # 'yellow',
    'rgba(128, 0, 128, 255)', # 'purple',
    'rgba(255, 0, 255, 255)', # 'magenta',
    'rgba(128, 0, 0, 255)', # 'maroon',
    'rgba(0, 255, 0, 255)', # 'lime',
    'rgba(0, 128, 128)', # 'teal'
]


class LevelWidget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)

        # data
        self.level = None
        self.cars = None

        # widgets
        self.editBtn = QPushButton("Edit")
        self.applyBtn = QPushButton("Apply")
        self.originalBoardTE = QTextEdit()
        self.originalBoardTE.setReadOnly(True)
        self.originalBoardTE.setStyleSheet("background: lightgrey")
        self.currentBoardTE = QTextEdit()
        self.currentBoardTE.setReadOnly(True)
        self.currentBoardTE.setStyleSheet("background: lightgrey")

        # layouts
        self.menuLayout = QHBoxLayout()
        self.menuLayout.addWidget(self.editBtn)
        self.menuLayout.addWidget(self.applyBtn)
        self.mainLayout = QVBoxLayout()
        self.mainLayout.addWidget(QLabel("Original Board"))
        self.mainLayout.addLayout(self.menuLayout)
        self.mainLayout.addWidget(self.originalBoardTE)
        self.mainLayout.addWidget(QLabel("Current Board"))
        self.mainLayout.addWidget(self.currentBoardTE)

        self.setLayout(self.mainLayout)

    def _parse_level(self, level):
        self.level = level
        cars = set([c for row in self.level for c in row if c != '.'])
        self.cars = dict((k, {"squares": [], "name": k, "color": "rgba(255, 0, 0, 255)" \
                          if k == 'X' else COLORS[i]}) for i, k in enumerate(cars))
        for i in range(6):
            for j in range(6):
                if self.level[i][j] in self.cars:
                    car = self.level[i][j]
                    self.cars[car]["squares"].append((i,j))

    def _validate_level(self, levelText):
        """
        return True if level valid, False otherwise
        """
        if len([line for line in levelText.splitlines() if line.strip()]) != 6:
            # wrong num rows
            return False
        
        if any(len(list(line)) != 6 for line in levelText.splitlines() if line.strip()):
            # wrong num cols
            return False

        return True

    def setOriginalLevel(self, level):
        # data
        self._parse_level(level)

        # original board
        self.originalBoardTE.setPlainText('\n'.join([''.join(square) for square in level]))
        cursor = self.originalBoardTE.textCursor()
        cursor.movePosition(QTextCursor.End)
        self.originalBoardTE.setTextCursor(cursor)

        # current board
        self.currentBoardTE.setPlainText('\n'.join([''.join(square) for square in level]))

    def setCurrentLevel(self, level):
        # data
        self._parse_level(level)

        # current board
        self.currentBoardTE.setPlainText('\n'.join([''.join(square) for square in level]))