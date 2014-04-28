import sys
import re

#http://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
def BronKerbosch2(r, p, x, ans, g):
    if len(p) == 0 and len(x) == 0:
        ans.append(r)
        return
    u = None
    for node in p|x:
        if u is None:
            u = node
        elif len(g[node]) > len(g[u]):
            u = node 
    for v in p-g[u]:
        BronKerbosch2(r|g[v], p&g[v], x&g[v], ans, g)
        p = p - set([v])
        x = x | set([v])

def main():
    g = {}
    edges = set()
    nodes = set()
    with open(sys.argv[1], "r") as f:
        for line in f:
            ptn = re.compile(r'[^ \t]+@[^ \t]+')
            f, t = re.findall(ptn, line.strip())
            edges.add((f, t))
            nodes.add(f)
            nodes.add(t)
    for n in nodes:
        g[n] = set()
    for f in nodes:
        for t in nodes:
            if f != t and (f, t) in edges and (t, f) in edges:
                g[f].add(t)
                g[t].add(f)
    ans = []
    BronKerbosch2(set(), nodes, set(), ans, g)
    for a in ans:
        emails = ''
        for u in sorted(list(a)):
            emails += "%s, " % u
        print emails[:-2]

if __name__ == '__main__':
    main()
