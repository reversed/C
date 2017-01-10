// regular expression matching supporting '.', '*', '$', '^'

#include <stdio.h>

int match(char *regexp, char *text)
{
    if (*regexp == '^')
        return matchhere(regexp+1, text);
    do {
        if (matchhere(regexp, text))
            return 1;
    } while (*text++ != '\0');
    return 0;
}

int matchhere(char *regexp, char *text)
{
    if (regexp[0] == '\0')
        return 1;
    if (regexp[1] == '*')
        return matchstar(regexp[0], regexp+2, text);
    if (regexp[0] == '$' && regexp[1] == '\0')
        return *text == '\0';
    if (*text != '\0' && (regexp[0] == '.' || regexp[0] == *text))
        return matchhere(regexp+1, text+1);
    return 0;
}

// shortest matching
int matchstar(int c, char* regexp, char* text)
{
    do {
        if (matchhere(regexp, text))
            return 1;
    } while (*text != '\0' && (*text++ == c || c == '.'));
    return 0;
}

// longest matching
int matchstar_l(int c, char* regexp, char* text)
{
    char *t;
    for (t = text; *t != '\0' && (*t == c || c == '.'); t++)
        ;
    do {
        if (matchhere(regexp, t))
            return 1;
    } while (t-- > text);
    return 0;
}

int main()
{
    char *s = "aab";
    char *p = "c*a*b";
    int res = match(p, s);
    printf("%d\n", res);
    return 0;
}




