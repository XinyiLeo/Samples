#!/usr/bin/python3
def leonardo(n):
    a, b = 1, 1
    seq = [a]
    while b < n:
        seq.append(b)
        a, b = b, a + b + 1
    return seq

if __name__ == "__main__":
    import sys
    print(leonardo(int(sys.argv[1])))
