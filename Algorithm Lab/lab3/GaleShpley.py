def find_stable_matching(MP, WP):
    n = len(MP)
    isManFree = [True] * n
    isWomanFree = [True] * n
    # isManProposed=[[False]*n]*n
    isManProposed = [[False for i in range(n)] for j in range(n)]
    match = [(-1, -1)] * n

    while (True in isManFree):
        indexM = isManFree.index(True)
        if (False in isManProposed[indexM]):
            indexW = -1
            for i in range(n):
                w = MP[indexM][i]
                if (not isManProposed[indexM][w]):
                    indexW = w
                    break
            isManProposed[indexM][indexW] = True
            if (isWomanFree[indexW]):
                # isManProposed[indexM][indexW]=True
                isWomanFree[indexW] = False
                isManFree[indexM] = False
                match[indexM] = (indexM, indexW)
            else:
                indexM1 = -1
                for j in range(n):
                    if (match[j][1] == indexW):
                        indexM1 = j
                        break
                if (WP[indexW].index(indexM) < WP[indexW].index(indexM1)):
                    isManFree[indexM1] = True
                    isManFree[indexM] = False
                    match[indexM] = (indexM, indexW)
    print(match)

find_stable_matching([ [2,1,0,3], [3,0,1,2],[2,3,0,1],[0,1,2,3] ] , [ [0,1,2,3],[0,3,2,1], [0,2,3,1],[0,2,1,3] ] )


# Cite from website