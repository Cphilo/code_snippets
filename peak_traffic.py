import sys
import re
import profile

#http://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
def BronKerbosch2(r, p, x, ans, g):
    if len(p) == 0 and len(x) == 0:
        if len(r) >= 3:ans.append(r)
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
    edges = set()
    nodes = set()
    ptn = re.compile(r'[^ \t]+@[^ \t]+')
    with open(sys.argv[1], "r") as f:
        for line in f:
            f, t = re.findall(ptn, line.strip())
            edges.add((f, t))
            nodes.add(f)
            nodes.add(t)
    g = {n:set() for n in nodes}
    lnodes = list(nodes)
    for i in range(len(nodes)):
        for j in range(i+1, len(nodes)):
            f = lnodes[i]
            t = lnodes[j]
            if (f, t) in edges and (t, f) in edges:
                g[f].add(t)
                g[t].add(f)
    ans = []
    BronKerbosch2(set(), nodes, set(), ans, g)
    emails = [", ".join(sorted(a)) for a in ans]
    for e in sorted(emails):
        print e

if __name__ == '__main__':
    main()
    #profile.run("main();")
