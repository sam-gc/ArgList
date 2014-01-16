#include "../arglist.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    ArgList alist = AL_Create(argc, argv);
    AL_ForEachUniqueKey(&alist, [](char *key, ALNode *node) {
        cout << key << endl;
        for(; node; node = node->next)
            cout << "\t" << (node->value ? node->value : "(null)") << endl;
    });

    AL_Free(&alist);
}