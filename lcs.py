import sys
import profile

def lcs(s1, s2, d):
    l1 = len(s1)
    l2 = len(s2)
    if l1 == 0 or l2 == 0:
        return ''
    if type(d[l1][l2]) == str:
        return d[l1][l2]
    if s1[-1] != s2[-1]:
        x1 = lcs(s1[:-1], s2, d)
        x2 = lcs(s1, s2[:-1], d)
        if len(x1) > len(x2):
            ans = x1
        else:
            ans = x2
    else:
        x3 = lcs(s1[:-1], s2[:-1], d)
        ans = x3+s1[-1]
    d[l1][l2] = ans
    return ans

def main():
    with open(sys.argv[1], "r") as f:
        for line in f:
            s1, s2 = line.strip().split(';')
            l1 = len(s1)
            l2 = len(s2)
            d = [[0]*(l2+1) for i in range(l1+1)]
            print lcs(s1, s2, d)
    sys.exit(0)

if __name__ == '__main__':
    #main()
    profile.run("main();")
