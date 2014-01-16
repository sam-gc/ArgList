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

typedef void (*ALNodeFunction)(char *key, ALNode *node);
typedef void (*ALSwitchFunction)(char *value);

ArgList AL_Create(int argc, char *argv[]);
void AL_Free(ArgList *lst);
int AL_Contains(ArgList *lst, char *key);
ALNode *AL_NodeForKey(ArgList *lst, char *key);
void AL_ForEachUniqueKey(ArgList *lst, ALNodeFunction nodefunc);
void AL_ForEachValueWithKey(ArgList *lst, char *key, ALSwitchFunction switchfunc);
void AL_ForEachValueInNode(ALNode *node, ALSwitchFunction switchfunc);
char *AL_FirstValueForKey(ArgList *lst, char *key);

#endif