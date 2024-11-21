board = [["*"] * 7 for _ in range(6)]


def print_board(board):
    for row in board:
        for cell in row:
            print(cell, " ", end="")
        print("")


def place_piece(board, yellow_player_turn):

    player = "".join(["Y" if yellow_player_turn else "R"])

    # get valid colum move for user
    condition = False
    while not condition:
        try:
            col = int(input("What colum: "))
        except ValueError:
            print("Please input valid number")
        if col >= 0 and col < 7:
            condition = True
        else:
            print("Please input valid number")

    # place piece in colum
    # checks from below if row is empthy
    # if row for col is empthy place piece
    for row in range(len(board) - 1, 0, -1):
        if board[row][col] == "*":
            board[row][col] = player
            break

    return board


def check_if_game_over(board):
    width = 7
    height = 6

    # horizontal
    for row in board:
        for col in range(width - 3):
            if (
                row[col] != "*"
                and row[col] == row[col + 1] == row[col + 2] == row[col + 3]
            ):
                return True

    # vertical
    for col in range(width):
        for row in range(height - 3):
            if (
                board[row][col] != "*"
                and board[row][col]
                == board[row + 1][col]
                == board[row + 2][col]
                == board[row + 3][col]
            ):
                return True

    # diagonal (top-left to bottom-right)
    for row in range(height - 3):
        for col in range(width - 3):
            if (
                board[row][col] != "*"
                and board[row][col]
                == board[row + 1][col + 1]
                == board[row + 2][col + 2]
                == board[row + 3][col + 3]
            ):
                return True

    # diagonal (bottom-left to top-right)
    for row in range(height-1, 2, -1):
        for col in range(width - 3):
            if (
                board[row][col] != "*"
                and board[row][col]
                == board[row - 1][col + 1]
                == board[row - 2][col + 2]
                == board[row - 3][col + 3]
            ):
                return True

    for row in board:
        if "*" in row:
            return False

    return True



def save_game(game, filepath="connect_4.txt"):
    out = ""
    for row in game:
        for cell in row:
            out += cell
        out += "\n"

    with open(filepath, "w") as f:
        f.write(out)

test = [
    ["*", "*", "*", "*", "*", "*", "*"],
    ["Y", "Y", "*", "Y", "*", "*", "*"],
    ["*", "*", "*", "R", "Y", "*", "*"],
    ["R", "*", "*", "R", "*", "R", "*"],
    ["R", "R", "Y", "Y", "R", "R", "*"],
    ["R", "Y", "Y", "Y", "R", "Y", "R"],
]

save_game(test)