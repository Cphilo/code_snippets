import sys
import bisect


class Line:
    def __init__(self, line):
        self.line = line

    def __cmp__(self, other):
        return cmp(-len(self.line), -len(other.line))

def main():
    with open(sys.argv[1], "r") as f:
        cnt = 0
        ss = []
        for ln in f:
            ln = ln.strip()
            if len(ln) == 0:continue
            if cnt == 0:
                n = int(ln)
                cnt = 1
            else:
                bisect.insort(ss, Line(ln))
                if len(ss) > n:ss.pop()
        for s in ss:print s.line

def test():
    line1 = Line("abc")
    line2 = Line("ss")
    line3 = Line("xy")
    print line1 < line2
    print line1 > line2
    print line2 == line3

if __name__ == "__main__":
    main()
    #test()
