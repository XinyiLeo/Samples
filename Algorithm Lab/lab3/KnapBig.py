def KnapBig(Weight,limit):
    n = len(Weight)
    Available = [True] * n
    Weight.sort()
    cur_weight = 0
    Final = []
    for i in range(n):
        if cur_weight + Weight[n - 1 - i] > limit:
            break
        else:
            Final.append(Weight[n - 1 - i])
            cur_weight += Weight[n - 1 - i]
    print(Final)

KnapBig([2,4,1,6,4,3],10)

