board = []
forsok = 10
current_round = 0


def lagbrett(forsok):
    global board
    guess = ["*", "*", "*", "*"]
    for i in range(forsok):
        board.append(guess)


def skrivut(board):
    step = 0
    for row in board:
        for cell in row:
            if step < 4:
                print(cell, end="")
                step += 1
            else:
                print("")
                step = 0


import random


def nykombinasjon():
    possible_picks = ["R", "O", "B", "G", "GR", "RO"]
    guess = []
    for i in range(4):
        guess.append(possible_picks[random.randint(0, len(possible_picks) - 1)])

    return guess


def lesinn():
    possible_picks = ["R", "O", "B", "G", "GR", "RO"]
    print("Possible picks: ", possible_picks)
    out = []
    while len(out) < 4:
        user_in = str(input("Skriv inn første farge: ")).upper()
        if user_in in possible_picks:
            out.append(user_in)
    return out


def nyttgjett(gjett):
    global board
    global current_round

    if current_round >= forsok:
        print("Du har brukt opp dine forsøk")
        exit()

    for i in range(len(board)):
        if i == current_round:
            board[i] = gjett

    current_round += 1


def evaluer(gjett, fasit):
    white = 0
    black = 0
    gjett_brukt = [False] * len(gjett)
    fasit_brukt = [False] * len(fasit)

    for i in range(len(fasit)):
        if gjett[i] == fasit[i] and gjett_brukt[i] == False and fasit_brukt[i] == False:
            white += 1
            gjett_brukt[i] = True
            fasit_brukt[i] = True

    for i in range(len(gjett)):
        if not gjett_brukt[i]:
            for j in range(len(fasit)):
                if not fasit_brukt[i] and gjett[i] == fasit[j]:
                    black += 1
                    fasit_brukt[i] = True
                    gjett_brukt[j] = True

    if white == 4:
        print("Du har vunnet")
        return

    print(
        f"{white} rett farge på rett plass (hvit) og {black} rett farge på fail plass (sort)"
    )


lagbrett(forsok)

gjett = ["R", "O", "O", "B"]
fasit = ["R", "R", "B", "B"]
evaluer(gjett, fasit)
