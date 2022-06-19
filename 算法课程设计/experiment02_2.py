def generate_cards(num):
	import random
	hand = [random.randint(1,11) for i in range(num)]
	random.shuffle(hand)
	random.shuffle(hand)
	return hand

import random

def black_jack_iterative(cards):
    global n
    n = len(cards)
    bj_table = {}
    bj_table[n] = 0
    for i in range(n-1,-1,-1):
        bj_table[i] = black_jack(cards, i,bj_table)
    return bj_table

def get_player_cards(cards,i,p):
    player_cards = []
    player_cards.append(cards[i])
    player_cards.append(cards[i+2])
    for k in range(0,p):
        player_cards.append(cards[i+4+k])
    return player_cards

def get_dealer_cards(cards,i,p,d):
    dealer_cards = []
    dealer_cards.append(cards[i + 1])
    dealer_cards.append(cards[i + 3])
    for k in range(0,d):
        dealer_cards.append(cards[i+4+p+k])
    return  dealer_cards

def black_jack(cards, i,bj_table):
    if n-i < 4:
        return 0
    options = []
    for p in range(0, n-i-3):
        player_cards = get_player_cards(cards, i, p)
        player = sum(player_cards)
        if player > 21:
            options.append(-1+bj_table[i+4+p])
            break

        for d in range(0, n-i-p-3):
            dealer_crards = get_dealer_cards(cards, i, p, d)
            dealer = sum(dealer_crards)
            if dealer >= 17:
                break
        if dealer >21:
            dealer = 0
        if player>dealer:
            flag=-1
        if player<dealer:
            flag=1
        if player==dealer:
            flag=0
        options.append(flag+bj_table[i+4+p+d])
    return max(options)


def experiment02():
    cards = generate_cards(108)
    j = 1
    for i, item in enumerate(black_jack_iterative(cards)):
        print('{}:{} \t'.format(item, cards[i]), end="")
        if (j == 10):
            print()
            j = 0
        j = j + 1

if __name__ == '__main__':
    experiment02()