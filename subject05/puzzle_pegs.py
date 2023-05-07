import numpy as np


# Coordinates for:
# Upper, Upper right, Upper left, Left, Right, Lower, Lower right, Lower left
x = np.array([2, 2, 2, 0, 0, -2, -2, -2])
y = np.array([0, 2, -2, -2, 2, 0, 2, -2])

# Board
# 0s: forbidden; 1s: Occupied; -1s: Free
board = np.zeros([5, 9])


def init_board():
    for row in range(5):
        for col in range(row, 9-row, 2):
            board[row][col] = 1

    x, y = map(int, input('Enter location of the empty hole (e.g. x y): ').split())
    board[x][y] = -1


def main():
    init_board()


if __name__ == '__main__':
    main()