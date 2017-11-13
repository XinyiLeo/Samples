import time
def bag(c, w, v):
    n = len(w)
    res = [[-1 for j in range(c + 1)] for i in range(n + 1)]
    for j in range(c + 1):
        res[0][j] = 0
    for i in range(1, n + 1):
        for j in range(1, c + 1):
            res[i][j] = res[i - 1][j]
            if j >= w[i - 1] and res[i][j] < res[i - 1][j - w[i - 1]] + v[i - 1]:
                res[i][j] = res[i - 1][j - w[i - 1]] + v[i - 1]

    print('The maximum value is:', res[n][c])
    x = [False for i in range(n)]
    j = c
    for i in range(1, n + 1):
        if res[i][j] > res[i - 1][j]:
            x[i - 1] = True
            j -= w[i - 1]
    print('The item we choose:',end='')
    for i in range(n):
        if x[i]:
            print(i,' ', end='')
    print('')

start = time.clock()
bag(15,[1,1,2,4,12],[1,2,2,10,4])
end = time.clock()
print(end-start)

#cite http://blog.csdn.net/littlethunder/article/details/26575417