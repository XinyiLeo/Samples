import math
file_object = open('thefile.txt','r')
inputt = file_object.readline()
print('The input is :'+ inputt)
list_p = inputt.split(' ')
intlist = [ int(i) for i in list_p ]

def mergecount(L1,L2):
    count = 0
    L = []
    a = len(L1)
    b = len(L2)
    i = 0
    j=0
    while i < a and j < b:
        if L1[i] <= L2[j]:
            L.append(L1[i])
            i+= 1
        else:
            L.append(L2[j])
            count += a-i+1
            j+=1
    if i >= a:
        L.extend(L2[j:])
    else:
        L.extend(L1[i:])
    return count,L



def sortcnt(L):
    count = 0
    if len(L) == 1:
        return 0, L
    else:
        L1, L2 = L[:math.floor(len(L) / 2)], L[math.floor(len(L) / 2):]
        count1, L1 = sortcnt(L1)
        count2, L2 = sortcnt(L2)
        count,L = mergecount(L1,L2)
    count += count1 + count2
    return count, L
cnt,LL = sortcnt(intlist)
print(cnt)
print(LL)

file_object.close()