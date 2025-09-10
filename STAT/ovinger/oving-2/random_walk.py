import numpy as np

def play_u1(n):
    wins = 0
    draws = 0
    loss = 0
    for _ in range(n):
        u1 = len(list(filter(lambda x: x > 0.51, [np.random.uniform(0,1) for _ in range(300)])))
        if u1 > n/2:
            wins += 1
        elif u1 == n/2:
            draws += 1
        else:
            loss += 1
        
    return wins, draws, loss

def play_u2(n):
    wins = 0
    draws = 0
    loss = 0

    for _ in range(n):
        u2 = []
        for _ in range(10):
            u2.append([np.random.uniform(0,1) for _ in range(30)])

        _wins = 0
        _draws = 0
        _loss = 0
        for l in u2:
            rounds_won = len(list(filter(lambda x: x > 0.51, l)))
            if rounds_won > 15:
                _wins += 1
            elif rounds_won == 15:
                _draws += 1
            else:
                _loss += 1

        if _wins > _loss:
            wins += 1
        elif _loss > _wins:
            loss += 1
        else:
            draws += 1
        
    
    return wins, draws, loss
    

    
n = 300
total_u1_wins = play_u1(n)
total_u2_wins = play_u2(n)
    
print("lang serie (w/d/l): ", total_u1_wins)    
print("flere spill (w/d/l): ", total_u2_wins)
