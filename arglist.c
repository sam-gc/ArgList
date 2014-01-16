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

            ALNode *nxt = (ALNode *)malloc(sizeof(ALNode));
            nxt->next = NULL;
            nxt->value = i < argc - 1 ? argv[i + 1] : NULL;
            cur->next = nxt;
        }
        else
        {
            struct ALChain *link = (struct ALChain *)malloc(sizeof(struct ALChain));
            link->key = argv[i];
            link->next = NULL;

            if(!last)
                arlist.head = link;
            else
                last->next = link;

            ALNode *node = (ALNode *)malloc(sizeof(ALNode));
            node->value = i < argc - 1 ? argv[i + 1] : NULL;
            node->next = NULL;
            link->list = node;

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
    for(; link; link = link->next)
    {
        if(strcmp(key, link->key) == 0)
            return link->list;
    }

    return NULL;
}

void AL_ForEachUniqueKey(ArgList *lst, ALNodeFunction nodefunc)
{
    struct ALChain *link = lst->head;
    for(; link; link = link->next)
        nodefunc(link->key, link->list);
}

void AL_ForEachValueWithKey(ArgList *lst, char *key, ALSwitchFunction switchfunc)
{
    AL_ForEachValueInNode(AL_NodeForKey(lst, key), switchfunc);
}

void AL_ForEachValueInNode(ALNode *node, ALSwitchFunction switchfunc)
{
    for(; node; node = node->next)
        switchfunc(node->value);
}

char *AL_FirstValueForKey(ArgList *lst, char *key)
{
    return AL_NodeForKey(lst, key)->value;
}