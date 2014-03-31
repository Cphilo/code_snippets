#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTOPS 310
#define MAXNODES 6000
#define MAXCOST 30000

int node_ref[MAXSTOPS][MAXNODES];
int g[MAXNODES][MAXNODES];
int visited[MAXNODES];
int nodeq[MAXNODES];
int costs[MAXNODES];    

int main(int argc, char ** argv)
{
    char line[1000];
    FILE * f = fopen(argv[1], "r");
    if(f == NULL) {
        exit(0);
    }
    int src, dst, i, j, k, read_cnt, offset, rti, nodei, start, station;
    int cnt, tmp, ans, res;
    int routes[500][200];
    char * rt, * c, *node, *data; 
    while(fgets(line, sizeof(line), f) != NULL) {
        line[strlen(line)-1] = '\0';
        rt = strtok(line, "; ");
        sscanf(rt, "(%d,%d)", &src, &dst);
        //printf("src: %d, dst: %d\n", src, dst);
        i = 0;
        while(rt = strtok(NULL, "; ")) {
            //printf("ugly route: %s\n", rt);
            j = 1;
            node = strchr(rt, ']');
            *node = '\0';
            node = strchr(rt, '[');
            node++;
            offset = 0;
            //printf("node %s\n", node);
            offset = 0;
            tmp = strlen(node);
            while(offset < tmp && 1==sscanf(node+offset, "%d,%n", &routes[i][j++], &read_cnt)) {
                offset += read_cnt;
            }
            /*printf("route %d\n", i);
            for(k=0;k<j;k++) {
                printf("%d ", routes[i][k]);
            }
            printf("\n");*/
            routes[i][0] = j-1;
            i++;
        }
        memset(node_ref, 0, MAXSTOPS * MAXNODES);
        for(k=0;k<MAXNODES;k++) {
            for(j=0;j<MAXNODES;j++) {
                g[k][j] = MAXCOST;
            }
        }
        start = 0;
        for(rti=0;rti<i;rti++) {
            //printf("route %d, count %d\n", rti, routes[rti][0]);
            for(nodei=1;nodei<=routes[rti][0];nodei++) {
                if(nodei < routes[rti][0]) {
                    g[start+nodei][start+nodei+1] = 7;
                    g[start+nodei+1][start+nodei] = 7;
                }
                //printf("nodei %d\n", nodei);
                station = routes[rti][nodei];
                cnt = node_ref[station][0];
                //printf("station %d, cnt %d\n", station, cnt);
                for(k=1;k<=cnt;k++) {
                    tmp = node_ref[station][k];
                    g[start+nodei][tmp] = 12;
                    g[tmp][start+nodei] = 12;
                }
                node_ref[station][cnt+1] = start+nodei;
                node_ref[station][0] = cnt+1;
            }   
            start += routes[rti][0];    
        }
        /*printf("create graph\n");
        for(i=0;i<MAXNODES;i++) {
            for(j=0;j<MAXNODES;j++) {
                if(g[i][j] < MAXCOST) {
                    printf("(%d %d):%d ", i, j, g[i][j]);
                }
            }
        }
        printf("\n");*/
        ans = MAXCOST;
        for(i=1;i<=node_ref[src][0];i++) {
            res = get_cost(node_ref[src][i], node_ref[dst]);
            if(res<ans) ans = res;
        }
        if(ans < MAXCOST) {
            printf("%d\n", ans);
        } else {
            printf("None\n");
        }
    }
    fclose(f);
    return 0;
}

int get_cost(int src, int dst[]) {
    int end = 0, node, head = 0, i, adj, d;
    int ans = MAXCOST;
    nodeq[end++] = src;
    for(i=0;i<MAXNODES;i++) {
        costs[i] = MAXCOST;
        visited[i] = 0;
    }
    costs[src] = 0;
    while(head<end) {
        node = nodeq[head++];
        visited[node] = 1;
        for(i=1;i<MAXNODES;i++) {
            if(g[node][i] < MAXCOST && visited[i] == 0) {
                nodeq[end++] = i;
                if (costs[i] > costs[node]+g[node][i]) {
                    costs[i] = costs[node]+g[node][i];
                }
            }
        }
    }
    for(i=1;i<=dst[0];i++) {
        d = dst[i];
        if(ans>costs[d])ans = costs[d];
    }
    return ans;    
}






