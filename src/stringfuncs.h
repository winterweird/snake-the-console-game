#ifndef SF_INITIALIZED
#include <stdio.h>
#include <stdlib.h>

char* toString(int);
void fill(char*, int, char);

char* toString(int n) {
    int len = 1;
    int a = n;
    while(a/=10) len++;
    
    char* ret = malloc((len+1) * sizeof *ret);
    fill(ret, len+1, '\0');
    for (a = len-1; a >= 0; a--) {
        ret[a] = n%10+'0';
        n/=10;
    }
    return ret;
}
void fill(char* str, int len, char ch) {
    for (int i = 0; i < len; i++) str[i] = ch;
}

#define SF_INITIALIZED
#endif