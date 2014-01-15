#include <stdlib.h>
#include <string.h>
#include "arglist.h"

struct ALChain {
    struct ALChain *next;
    ALNode *list;
    char *key;
};

ArgList AL_Create(int argc, char *argv[])
{
    ArgList arlist = {NULL};

    struct ALChain *last = NULL;
    
    int i;
    for(i = 0; i < argc; i++)
    {
        ALNode *cur = AL_NodeForKey(&arlist, argv[i]);
        if(cur)
        {
            while(cur->next)
                cur = cur->next;

            ALNode *nxt = malloc(sizeof(ALNode));
            nxt->next = NULL;
            nxt->value = i < argc - 1 ? argv[i + 1] : NULL;
            cur->next = nxt;
        }
        else
        {
            struct ALChain *link = malloc(sizeof(struct ALChain));
            link->key = argv[i];
            link->next = NULL;

            if(!last)
                arlist.head = link;
            else
                last->next = link;

            if(i < argc - 1)
            {
                ALNode *node = malloc(sizeof(ALNode));
                node->value = argv[i + 1];
                node->next = NULL;
                link->list = node;
            }
            else
                link->list = NULL;

            last = link;
        }
    }

    return arlist;
}

void AL_Free(ArgList *lst)
{
    struct ALChain *link = lst->head;
    while(link)
    {
        ALNode *node = link->list;
        while(node)
        {
            ALNode *prev = node;
            node = node->next;
            free(prev);
        }

        struct ALChain *prev = link;
        link = link->next;
        free(prev);
    }
}

int AL_Contains(ArgList *lst, char *key)
{
    return AL_NodeForKey(lst, key) != NULL;
}

ALNode *AL_NodeForKey(ArgList *lst, char *key)
{
    struct ALChain *link = lst->head;
    for(link; link; link = link->next)
    {
        if(strcmp(key, link->key) == 0)
            return link->list;
    }

    return NULL;
}