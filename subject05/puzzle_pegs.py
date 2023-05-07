import numpy as np


# Coordinates (o_x, o_y) for:
# Upper, Upper right, Upper left, Left, Right, Lower, Lower right, Lower left
dx = np.array([4, 2, 2, 0, 0, -4, -2, -2])
dy = np.array([0, 2, -2, -4, 4, 0, 2, -2])


class Board():
    def __init__(self):
        # 0s: forbidden; 1s: Occupied; -1s: Free
        self.board = np.zeros([5, 9], dtype=int)
        self.answer = np.zeros(9999, dtype=int)

        for row in range(5):
            for col in range(row, 9-row, 2):
                self.board[row][col] = 1

        x, y = map(int, input('Enter location of the empty hole (e.g. x y): ').split())
        self.board[x][y] = -1

    def show_curr_answer(self):
        for index in range(2, len(self.answer) - 1, 2):
            print(self.answer[index], '->', self.answer[index + 1])

    def solve(self):
        trace = np.array([[-1, -1], [-1, -1]])
        self.backtrack(self.board, 14, trace)
        self.show_curr_answer()

    def backtrack(self, state, num_pegs, trace):
        global dx, dy

        # If done, update answer
        if num_pegs == 1:
            if len(self.answer) > len(trace):
                self.answer = trace.copy()
                return

        # Otherwise, move the peg (x, y)
        for x in range(5):
            for y in range(9):
                if state[x][y] == 1:
                    for i in range(len(dx)):
                        _x = x + dx[i]
                        _y = y + dy[i]

                        # Check if dest is inside the board and is empty AND immediate hole is occupied
                        if is_inside_board(_x, _y) and state[_x][_y] == -1 and state[(x + _x)//2][(y + _y)//2] == 1:
                            state[x][y] = -1
                            state[_x][_y] = 1
                            state[(x + _x)//2][(y + _y)//2] = -1
                            num_pegs = num_pegs - 1
                            trace = np.append(trace, [[x, y], [_x, _y]], axis=0)

                            self.backtrack(state, num_pegs, trace)

                            # Undo
                            state[x][y] = 1
                            state[_x][_y] = -1
                            state[(x + _x)//2][(y + _y)//2] = 1
                            num_pegs = num_pegs + 1
                            trace = trace[:len(trace) - 2]


def is_inside_board(x, y):
    if 0 <= x <= 4 and 0 <= y <= 8:
        return True
    return False


def main():
    board = Board()
    board.solve()


if __name__ == '__main__':
    main()