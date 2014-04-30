import sys

def main():
    with open(sys.argv[1], "r") as f:
        for line in f:
            olds, fr = line.strip().split(";")
            fr = fr.split(',')
            pairs = [(fr[i], fr[i+1]) for i in range(0, len(fr), 2)]
            rs = [(olds, 0)]
            swaps = []
            #print rs
            for p in pairs:
                for rsi, s in enumerate(rs):
                    i = s[0].find(p[0])
                    if i>= 0:
                        x = s[1] + i
                        del rs[rsi]
                        if i>0:
                            rs.append((s[0][:i], s[1]))
                        e = i+len(p[0])
                        if e < len(s[0]):
                            rs.append((s[0][e:], x+len(p[0])))
                        swaps.append((p[0], p[1], x))
                        #print rs
                        break 
            #print "olds: %s, swaps: %s" % (olds, swaps)
            ans = ''
            lasti = 0
            for swap in sorted(swaps, key=lambda x: x[2]):
                ans += olds[lasti:swap[2]]+swap[1]
                lasti = swap[2] + len(swap[0])
            ans += olds[lasti:]
            print ans

if __name__ == '__main__':
    main()
