#ifndef ARGLIST_H
#define ARGLIST_H

typedef struct node{
    char *key;
    char *value;

    node *next;
} ALNode;

typedef struct {
    ALNode *head;
} ArgList;

ArgList AL_Create(int argc, char *argv[]);
void AL_Free(ArgList *lst);
int AL_Contains(ArgList *lst, char *key);
ALNode *AL_NodeForKey(ArgList *lst, char *key);

#endif