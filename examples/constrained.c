#include <stdio.h>
#include "../arglist.h"

void print_contents(char *key, ALNode *node)
{
    printf("%s\n", key);
    for(; node; node = node->next)
        printf("\t%s\n", node->value);
}

int main(int argc, char *argv[])
{
    ArgList alist = AL_CreateWithContraints(argc, argv, 0, "hello");

    AL_ForEachUniqueKey(&alist, &print_contents);

    AL_Free(&alist);

    return 0;
}
