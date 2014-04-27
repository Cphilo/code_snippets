import sys 

def main():
    with open(sys.argv[1], "r") as f:
        for line in f:
            num = int(line)
            mnum = 0
            ln = map(int, list(line.strip()))
            for x in reversed(sorted(ln)):
                mnum = 10*mnum + x
            if num < mnum:
                j = get_firstj(ln)
                dd = ln[:j+1]
                for x in sorted(ln[j+1:]):
                    dd.append(x)
            else:
                ln.append(0)
                dd = [x for x in sorted(ln)]
                for i in range(len(dd)):
                    if dd[i]:
                        dd[i], dd[0] = dd[0], dd[i]
                        break
            ans = 0
            for d in dd:
                ans = 10*ans + d         
            print ans

def get_firstj(line):
    for i in range(len(line)-1, -1, -1):
        for j in range(i-1, -1, -1):
            if line[i] > line[j]:
                line[i], line[j] = line[j], line[i]
                return j
    return -1 

if __name__ == "__main__":
    main()
