#ifndef ARGLIST_H
#define ARGLIST_H

#ifdef __cplusplus
#include <functional>
extern "C" {
#endif

struct ALChain;

typedef struct node{
    char *value;

    struct node *next;
} ALNode;

typedef struct {
    struct ALChain *head;
} ArgList;

#ifdef __cplusplus
}
typedef std::function<void(char *key, ALNode *node)> ALNodeFunction;
typedef std::function<void(char *value)> ALSwitchFunction;
extern "C" {
#else
typedef void (*ALNodeFunction)(char *key, ALNode *node);
typedef void (*ALSwitchFunction)(char *value);
#endif

ArgList AL_Create(int argc, char *argv[]);
ArgList AL_CreateWithContraints(int argc, char *argv[], int dieOnErr, ...);
void AL_Free(ArgList *lst);
int AL_Contains(ArgList *lst, char *key);
ALNode *AL_NodeForKey(ArgList *lst, char *key);

void AL_ForEachUniqueKey(ArgList *lst, ALNodeFunction nodefunc);
void AL_ForEachValueWithKey(ArgList *lst, char *key, ALSwitchFunction switchfunc);
void AL_ForEachValueInNode(ALNode *node, ALSwitchFunction switchfunc);

char *AL_FirstValueForKey(ArgList *lst, char *key);

#ifdef __cplusplus
}
#endif

#endif