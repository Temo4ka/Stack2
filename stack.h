#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int MAX_SIZE = 10010;

enum StackError {
        stackOk     = 0,
    stackNullCaught = 1,
     stackOverflow  = 2,
};

struct Stack {
    void *data  ;
    int   size  ;
    int capacity;
    int elemSize;
};

struct List {
    struct List *prev;
    void        *data;
    int      elemSize;
};

#define catchNullptr(POINTER, RETURN_VALUE,...) {                                                                  \
    if ((POINTER) == NULL) {                                                                                        \
        fprintf(stderr, "%s pointer at %s at %s(%d) is NULL\n", #POINTER, __PRETTY_FUNCTION__, __FILE__, __LINE__);  \
        __VA_ARGS__;                                                                                                  \
        return RETURN_VALUE;                                                                                           \
    }                                                                                                                   \
}

struct Stack* stackCtor(size_t size, size_t elemSize);

int stackPush(struct Stack *stack, void *buffer);

int stackPop(struct Stack *stack);

int stackTop(struct Stack *stack, void *buffer);

struct Stack* stackDtor(struct Stack *stack);

struct List* listCtor(size_t elemSize);

int listPush(struct List **list, void *buffer);

int listPop(struct List **list);

int listTop(struct List *list, void *buffer);

struct List* listDtor(struct List *list);

int testStack1(struct Stack *stack);

int testList1 (struct List **list);

int testStack2(struct Stack *stack);

int testList2(struct List **list);

int testStack3(struct Stack *stack);

int testList3(struct List **list);

