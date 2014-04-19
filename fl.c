#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double change(char s[], int l)
{
    if(s[l-1] == 'x' && s[l-2]=='p')
    {
        s[l-2] = '\0';
        return atof(s);
    }
    char c = s[l-2];
    if(c>='0' && c <= '9') {
        s[l-1] = '\0';
        return atof(s)*1000;
    }
    s[l-2] = '\0';
    if(c == 'd') {
        return 100*atof(s);
    } else if(c == 'c') {
        return 10*atof(s);
    } else if(c == 'm') {
        return atof(s); 
    } else if(c == 'u') {
        return atof(s)/1000;
    } else if(c == 'n') {
        return atof(s)/1000000;
    }
}

int main()
{
    int t, kase;
    char s1[100], s2[100], s3[100];
    int fl, cl, il;
    double f, c, i, ans;
    scanf("%d", &t);
    for(kase=1;kase<=t;kase++) {
        scanf("%s%s%s", s1, s2, s3);
        fl = strlen(s1);
        f = change(s1, fl);
        cl = strlen(s2);
        c = change(s2, cl);
        il = strlen(s3);
        i = change(s3, il);
        ans = round((i*f/c) * 100)/100;
        printf("Case %d: %.2fpx\n", kase, ans);
    }
    return 0;
}

