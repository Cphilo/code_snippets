#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reverse_str(char *s)
{
    char c[200], tmp[200];
    int l = strlen(s);
    if(l==0) {
        return "";
    }
    strcpy(tmp, s+l-1);
    strcpy(c, s);
    c[l-1] = '\0';
    return strcat(tmp, reverse_str(c));
}

int main()
{
    char * test = "hello, world!";
    //printf("reverse %s:", test);
    printf("reverse %s: %s\n", test, reverse_str(test)); 
    return 0;
}

