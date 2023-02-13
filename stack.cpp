#include "stack.h"

int main () {
    struct Stack *stack = stackCtor(1, sizeof(int)); 
    struct List   *list = listCtor (   sizeof(int));

    int elem = 1;

    testList1(&list);
    // testList2(list);
    // testList3(list);
    testStack1(stack);
    // testStack2(stack);
    // testStack3(stack);

    return 0;
}

int testStack1(struct Stack *stack) {
    int elem = rand();

    for (int i = 0; i < 1e6; i++)
        stackPush(stack, &elem);
    for (int i = 0; i < 9; i++) {
        for (int i = 0; i < stack -> size / 2; i++)
            stackPop(stack);
        for (int i = 0; i < stack -> size / 4; i++)
            stackPush(stack, &elem);
    }

    return 0;
}

int testList1 (struct List **list) {
    int elem = rand();
    int size =   1e6 ;

    for (int i = 0; i < 1e6; i++)
        listPush(list, &elem);
    for (int i = 0; i < 9; i++) {
        for (int i = 0; i < size / 2; i++)
            listPop(list);
        size /= 2;
        for (int i = 0; i < size / 2; i++)
            listPush(list, &elem);
        size += size / 2;
    }

    return 0;
}

int testStack2(struct Stack *stack) {
    int elem = rand();

    for (int i = 0; i < 1e6; i++)
        stackPush(stack, &elem);
    
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 10000; j++)
            stackPush(stack, &elem);
        for (int j = 0; j < 10000; j++)
            stackPop(stack);
    }

    for (int i = 0; i < 9; i++) {
        for (int i = 0; i < stack -> size / 2; i++)
            stackPop(stack);
        for (int i = 0; i < stack -> size / 4; i++)
            stackPush(stack, &elem);
    }

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 10000; j++)
            stackPush(stack, &elem);
        for (int j = 0; j < 10000; j++)
            stackPop(stack);
    }

    return 0;
}

int testList2(struct List **list) {
    int elem = rand();
    int size =   1e6 ;

    for (int i = 0; i < 1e6; i++)
        listPush(list, &elem);
    
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 10000; j++)
            listPush(list, &elem);
        for (int j = 0; j < 10000; j++)
            listPop(list);
    }

    for (int i = 0; i < 9; i++) {
        for (int i = 0; i < size / 2; i++)
            listPop(list);
        size /= 2;
        for (int i = 0; i < size / 2; i++)
            listPush(list, &elem);
        size += size / 2;
    }

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 10000; j++)
            listPush(list, &elem);
        for (int j = 0; j < 10000; j++)
            listPop(list);
    }

    return 0;
}

int testStack3(struct Stack *stack) {
    int elem = rand();

    for (int i = 0; i < 1e6; i++)
        stackPush(stack, &elem);
    
    for (int i = 0; i < 1e6; i++)
        if (rand() % 2 == 0)
            stackPush(stack, &elem);
        else
            stackPush(stack, &elem);
    
    return 0;
}

int testList3(struct List **list) {
    int elem = rand();

    for (int i = 0; i < 1e6; i++)
        listPush(list, &elem);
    
    for (int i = 0; i < 1e6; i++)
        if (rand() % 2 == 0)
            listPush(list, &elem);
        else
            listPush(list, &elem);
    
    return 0;
}

struct Stack* stackCtor(size_t size, size_t elemSize) {
    struct Stack *stack = (struct Stack *) calloc(size, sizeof(struct Stack));

    stack -> capacity =                size                 ;
    stack ->   data   = (void *) calloc(1, sizeof(elemSize));
    stack ->   size   =                 0                   ;
    stack -> elemSize =              elemSize               ;

    return stack;
}

int stackPush(struct Stack *stack, void *buffer) {
    // fprintf(stderr, "%d!!\n", stack -> size);
    if (stack -> size == stack -> capacity) {
        stack -> data = (void *) realloc(stack -> data, stack -> capacity * 2 * stack -> elemSize);

        stack -> capacity *= 2;
    }

    void *top = (char *) stack -> data + stack -> elemSize * stack -> size;

    memcpy(top, buffer, stack -> elemSize);
    stack -> size++;

    return 1;
}

int stackPop(struct Stack *stack) {  
    if (stack -> size <= 0) {
        fprintf(stderr, "error\n");
        return 0;
    }

    stack -> size--;

    return 1;
}

int stackTop(struct Stack *stack, void *buffer) {
    if (stack -> size == 0) {
        printf("error\n");
        return 1;
    }

    void *top = (char *) stack -> data + stack -> elemSize * (stack -> size - 1);
    memcpy(buffer, top, stack -> elemSize);

    return 1;
}

struct Stack* stackDtor(struct Stack *stack) {
    free(stack -> data);
    free(stack);

    return nullptr;
}

struct List* listCtor(size_t elemSize) {
    struct List *list = (struct List *) calloc(1, sizeof(struct List));

    list ->   data   = (void *) calloc(1, sizeof(elemSize));
    list ->   prev   =                list                 ;
    list -> elemSize =              elemSize               ;

    return list;
}

int listPush(struct List **list, void *buffer) {
    struct List *newNode = listCtor((*list) -> elemSize);

    memcpy(newNode -> data, buffer, (*list) -> elemSize);
    newNode -> prev = *list;
    *list = newNode;

    return 1;
}

int listPop(struct List **list) {    
    if ((*list) -> prev == (*list)) {
        printf("error\n");
        return 0;
    }

    struct List *newNode = (*list) -> prev;
    // listDtor(*list);
    (*list) = newNode;

    return 1;
}

int listTop(struct List *list, void *buffer) {
    if (list -> prev == list) {
        printf("error\n");
        return 0;
    }

    memcpy(buffer, list -> data, list -> elemSize);

    return 1;
}

struct List* listDtor(struct List *list) {
    free(list -> data);
    free(list);

    return nullptr;
}