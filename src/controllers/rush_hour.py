class RushHour:
    UP = 0
    DOWN = 1
    LEFT = 2
    RIGHT = 3

    HORIZONTAL = 0
    VERTICAL = 1

    def __init__(self, board):
        """
        board is a 6x6 char array
        """
        self.board = board

    def make_move(self, carName, dir, length):
        """
        moves car with given name for length steps in the given direction
        - return True if move is valid, False otherwise
        """
        squares = [(i, j) for i in range(6) for j in range(6) if self.board[i][j] == carName]
        rotation = self.HORIZONTAL if any(s[1] != squares[0][1] for s in squares[1:]) else self.VERTICAL

        # check if dir conflicts with rotation
        if rotation == self.HORIZONTAL and dir not in [self.LEFT, self.RIGHT] or \
                rotation == self.VERTICAL and dir not in [self.UP, self.DOWN]:
            return False

        # check for edge of board and collisions
        for i in range(1, length+1):
            edge = squares[0] if dir in [self.LEFT, self.UP] else squares[-1]
            new_edge = (edge[0], edge[1] - i) if dir == self.LEFT \
                else (edge[0], edge[1] + i) if dir == self.RIGHT \
                else (edge[0] - i, edge[1]) if dir == self.UP \
                else (edge[0] + i, edge[1]) if dir == self.DOWN \
                else None
            
            # check if boundary check satisifed
            if new_edge[0] < 0 or new_edge[0] >= 6 or new_edge[1] < 0 or new_edge[1] >= 6:
                return False

            # check for collision
            if self.board[new_edge[0]][new_edge[1]] != '.':
                return False

        # get the new squares after the move
        new_squares = [(square[0], square[1] - length) if dir == self.LEFT \
            else (square[0], square[1] + length) if dir == self.RIGHT \
            else (square[0] - length, square[1]) if dir == self.UP \
            else (square[0] + length, square[1]) if dir == self.DOWN \
            else None for square in squares]
    
        # perform the move
        for square in squares:
            self.board[square[0]][square[1]] = '.'

        for square in new_squares:
            self.board[square[0]][square[1]] = carName

        return True


    @staticmethod
    def is_solved():
        """
        return True if and only if the board is solved
        i.e. the XX car is touching the right edge of the board
        """
        # TODO implement me
        pass