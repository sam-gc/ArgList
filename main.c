#include <stdio.h>
#include "arglist.h"

void print_contents(char *key, ALNode *node)
{
    printf("%s\n", key);
    for(; node; node = node->next)
        printf("\t%s\n", node->value);
}

int main(int argc, char *argv[])
{
    ArgList alist = AL_Create(argc, argv);

    ALNode *node = AL_NodeForKey(&alist, "hello");
    
    if(node)
        printf("Key \"hello\" yieled value \"%s\"\n", node->value);

    AL_ForEachUniqueKey(&alist, &print_contents);

    return 0;
}
