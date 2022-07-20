import sys

INT_MIN = -sys.maxsize - 1
INT_MAX = sys.maxsize


def trapRainwater(levels: list):
    i = 0
    j = len(levels) - 1
    mini = INT_MIN
    minj = INT_MIN
    while i < j:
        if mini != INT_MIN:
            if levels[i] < mini:
                sum += mini - levels[i]
            elif levels[i] > mini:
                mini = levels[i]
        if minj != INT_MIN:
            if levels[j] < minj:
                sum += minj - levels[j]
            elif levels[j] > minj:
                minj = levels[j]
        i += 1
        j -= 1
    return sum
