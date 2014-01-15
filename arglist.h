#ifndef ARGLIST_H
#define ARGLIST_H

struct ALChain;

typedef struct node{
    char *value;

    struct node *next;
} ALNode;

typedef struct {
    struct ALChain *head;
} ArgList;

ArgList AL_Create(int argc, char *argv[]);
void AL_Free(ArgList *lst);
int AL_Contains(ArgList *lst, char *key);
ALNode *AL_NodeForKey(ArgList *lst, char *key);

#endif