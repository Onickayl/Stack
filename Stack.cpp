#include <stdio.h>
#include <TXLib.h>

typedef double StackElem;

struct Stack
{
    StackElem* data;
    int size;
    int capacity;
};

int StackConstructor(Stack* stk, int capacity);
int StackDestructor(Stack* stk);

void StackDump(Stack* stk);
int StackCheck(Stack* stk);

int StackPush(Stack* stk, StackElem value);
int StackPop(Stack* stk);


int main()
{
    Stack stk = {};

    StackConstructor(&stk, 10);

    StackDump(&stk);

    StackPush(&stk, 100);
    StackPush(&stk, 200);
    StackPush(&stk, 300);

    StackDump(&stk);

    StackPop(&stk);

    StackDump(&stk);

    StackDestructor(&stk);


    StackDump(&stk);
    return 0;

}

int StackConstructor(Stack* stk, int capacity)
{
    stk->data = (StackElem*) calloc(capacity, sizeof(StackElem));

    if (stk->data == NULL)
    {
        return -1;    // change
    }

    stk->size = 0;
    stk->capacity = capacity;

    return 0;

}


int StackDestructor(Stack* stk)
{
    free(stk->data);

    stk->size = -1;
    stk->capacity = -1;
    stk->data = NULL;

    return 0;

}

void StackDump(Stack* stk)
{
    FILE* fp;

    if ((fp = fopen("dump.txt", "a+")) == NULL)
    {
        fprintf(stdout, "Не удается открыть файл \"dump.txt\".\n") ;
        exit(EXIT_FAILURE);
    }

    if (stk->data != NULL)
    {
        for (int i = 0; i < stk->size; i++)
        {
            fprintf(fp, "%lg ", stk->data[i]);
        }
    }
    else
    {
        fprintf(stdout, "Нулевой указатель\n");
    }


    fprintf(fp, "\n");

    fprintf(fp, "size = %d\n", stk->size);

    fprintf(fp, "capacity = %d\n", stk->capacity);

    fprintf(fp, "\n\n");

    if (fclose(fp) != 0)
    {
        fprintf (stderr, "Ошибка при закрытии файла\n");
    }

}

int StackCheck(Stack* stk)
{
    if (stk->capacity < stk->size)
    {
        return -1;
    }

    if (stk->size < 0 || stk->capacity < 0)
    {
        return -1;
    }

    if (stk->data == NULL)
    {
        return -1;
    }

    return 0;
}

int StackPush(Stack* stk, StackElem value)
{
    if (StackCheck(stk)!= 0)
    {
        StackDump(stk);
        return -1;
    }

    /*if (size >= capacity)
    {
    // more capacity
        realloc(Stack* stk->data, size_t size)
    }   */

    stk->data[stk->size] = value;

    stk->size++;


    if (StackCheck(stk)!= 0)
    {
        StackDump(stk);
        return -1;
    }

    return 0;

}

int StackPop(Stack* stk)
{
    if (StackCheck(stk)!= 0)
    {
        StackDump(stk);
        return -1;
    }


    /*if (size >= capacity)
    {
    // more capacity
    }   */

    if (stk->size < 0)
    {
        return -1;
    }

    stk->data[stk->size] = 0;

    stk->size--;

    if (StackCheck(stk)!= 0)
    {
        StackDump(stk);
        return -1;
    }
}

