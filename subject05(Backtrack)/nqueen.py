import numpy as np

# global variables
board = []
result = []
queen = []
n = 0

def create_chessboard(queen):
    # Used to create a matrix represents a correct answer
    chessboard = []
    for row in range(n):
        chessboard.append('.'*(queen[row])+'Q'+ '.'*(n-queen[row]-1))
    return chessboard


def safe(queen,row,col):
    # Check if current position is safe
    for i in range(row):
        if col == queen[i] or queen[i]-i == col - row or queen[i]+i == col+row:
            return False

    return True
    

def backtrack(row,queen):
    if row == n:
        # All n queens are placed, save the placements to list of answers
        result.append(create_chessboard(queen))
        return

    for col in range(n):
        flag = safe(queen,row,col)
        if flag:
            # Current queen cannot attack previous queens
            queen[row] = col
            backtrack(row+1,queen)


##### Main code #####
n = int(input())
# Initiate list of queens, rows and columns are numbered from 0 to n-1 
queen = [0 for i in range(n)]
backtrack(0,queen)
print(result)

