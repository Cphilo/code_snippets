import sys
import profile
import array
import collections

def main():
    with open(sys.argv[1], "r") as f:
        for line in f.readlines():
            data = line.strip().split('; ') 
            src, dst = map(int, data[0].strip('()').split(','))
            routes = [map(int, r.split('=')[1].strip('[]').split(',')) for r in data[1:]]
            #create a graph with the routes 
            #print "routes: %s" % routes
            start = 0
            g = {}
            node_ref = {}
            for r in routes:
                rlen = len(r)
                for i in range(rlen):
                    if i < rlen-1:
                        if start+i not in g:
                            g[start+i] = [(start+i+1, 7)]
                        else:
                            g[start+i].append((start+i+1, 7))
                        if start+i+1 not in g:
                            g[start+i+1] = [(start+i, 7)]
                        else:
                            g[start+i+1].append((start+i, 7))
                    if r[i] in node_ref:
                        for node in node_ref[r[i]]:
                            g[start+i].append((node, 12))
                            g[node].append((start+i, 12))
                    if r[i] not in node_ref:
                        node_ref[r[i]] = [start+i]
                    elif start+i not in node_ref[r[i]]:
                        node_ref[r[i]].append(start+i)
                start += rlen
            #print "create graph: %s" % g
            ans = 100000000
            #print node_ref[src]
            for s in node_ref[src]:
                visited = [False] * start
                costs = [100000000] * start
                costs[s] = 0
                get_cost(s, g, visited, costs)
                res = min([costs[node] for node in node_ref[dst]])
                if res < ans:ans = res
            if ans == 100000000:
                print "None"
            else:
                print ans
    sys.exit(0)

def get_cost(src, g, visited, costs):
    nq = collections.deque()
    nq.append(src)
    costs[src] = 0
    while nq:
        curnode = nq.popleft()
        visited[curnode] = True
        for (node, w) in g[curnode]:
            if not visited[node]:
                nq.append(node)
                if costs[node] > costs[curnode] + w:
                    costs[node] = costs[curnode] + w 

def test():
    g = {0: [(1, 7)], 1: [(0, 7), (2, 7)], 2: [(1, 7)], 3: [(4, 7), (11, 12)], 4: [(3, 7), (5, 7)], 5: [(4, 7), (6, 7)], 6: [(5, 7), (7, 7)], 7: [(6, 7)], 8: [(9, 7)], 9: [(8, 7), (10, 7)], 10: [(9, 7), (11, 7)], 11: [(10, 7), (3, 12)]}
    visited = [False] * 12
    costs = [100000000] * 12
    s = 3
    get_cost(s, g, visited, costs)
    print "src %d, costs: %s" % (s, costs) 
    #get_cost(3, g, visited, costs)
    #print "src 3, costs: %s" % 

if __name__ == '__main__':
    #profile.run("main();")
    main()
