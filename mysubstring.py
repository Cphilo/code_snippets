import sys
import re

def mysub(s, sub):
    #mysub('Hello',ell)->true
    #mysub('ko','*l')->false
    #mysub('ko*', '\*')->true
    si = 0
    subi = 0
    last_si = 0
    is_escape = 0
    while si < len(s) and subi < len(sub):
        if sub[subi] == '*' and not is_escape:
            last_si = si if subi == 0 else last_si
            if subi == len(sub)-1:
                subi += 1
            elif s[si] == sub[subi+1]:
                subi += 1 
            else:
                si += 1
        elif sub[subi] == s[si]:
            last_si = si if subi == 0 else last_si
            subi += 1
            si += 1
        elif sub[subi] == '\\':
            subi += 1
            is_escape = 1 
        else:
            subi = 0
            si = last_si + 1
            last_si = si
            is_escape = 0
    return "true" if subi == len(sub) else "false"

def main():
    with open(sys.argv[1], "r") as f:
        for line in f:
            s, sub = line.strip().split(',')
            #match = re.search(sub, s) 
            #print "false" if match is None else "true"
            print mysub(s, sub)

if __name__ == '__main__':
    main()
