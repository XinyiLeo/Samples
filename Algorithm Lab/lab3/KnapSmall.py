def KnapBig(Weight,limit):
    n = len(Weight)
    Available = [True] * n
    Weight.sort()
    cur_weight = 0
    Final = []
    for i in range(n):
        if cur_weight + Weight[i] > limit:
            break
        else:
            Final.append(Weight[i])
            cur_weight += Weight[i]
    print(Final)

KnapBig([2,5,1,6,4,3],10)

