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

/**
 * Parses command line options and returns an "ArgList" struct that contains
 * a reference to the head of the internal structure. No constraints.
 */
ArgList AL_Create(int argc, char *argv[]);

/**
 * Same as AL_Create, but lets you specify a list of allowed switches. The
 * additional parameter "dieOnErr" determines whether or not the program
 * should close if there is an unknown parameter.
 **/
ArgList AL_CreateWithContraints(int argc, char *argv[], int dieOnErr, ...);

/**
 * Cleans up after the argument list by freeing allocated memory compents
 * inside the internal structure.
 **/
void AL_Free(ArgList *lst);

/**
 * Given the pointer to an ArgList gien, return a boolean value that is true
 * iff the string represented by "key" is one of the parameters
 **/
int AL_Contains(ArgList *lst, char *key);

/**
 * Return the head of a linked list of ALNodes that have the key of "key".
 **/
ALNode *AL_NodeForKey(ArgList *lst, char *key);

/**
 * Utility function to iterate over each unique key in the list. For each
 * unique key, "nodefunc" will be called with its first parameter being the
 * key in question and the second parameter being the head of a linked list
 * of ALNodes, the same as that returned from "AL_NodeForKey()". nodefunc
 * can be a function pointer or, in C++11 mode, a lambda.
 **/
void AL_ForEachUniqueKey(ArgList *lst, ALNodeFunction nodefunc);

/**
 * Utility function to iterate over each value that matches "key".
 * "switchfunc" will be called for each node with its sole parameter being
 * the value for that node. Once again, this can be a function pointer or
 * a lambda.
 **/
void AL_ForEachValueWithKey(ArgList *lst, char *key, ALSwitchFunction switchfunc);

/**
 * Given the head of a linked list, do as "AL_ForEachValueWithKey()"
 * without necessarily knowing the key. AL_ForEachValueWithKey() uses this
 * function internally.
 **/
void AL_ForEachValueInNode(ALNode *node, ALSwitchFunction switchfunc);

char *AL_FirstValueForKey(ArgList *lst, char *key);

#ifdef __cplusplus
}
#endif

#endif