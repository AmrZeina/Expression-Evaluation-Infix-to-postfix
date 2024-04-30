#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node
{
    float data;
    struct node* next;
} node;

typedef struct
{
    node* top;
} stack;

stack* initialize()
{
    stack* s = malloc(sizeof(stack));
    s->top = NULL;
    return s;
}

node* newnode(float x)
{
    node* n = malloc(sizeof(node));
    n->data = x;
    n->next = NULL;
    return n;
}

int isEmpty(stack* s)
{
    return s->top == NULL;
}

void push(stack* s, float x)
{
    node* n = newnode(x);
    if (isEmpty(s))
    {
        s->top = n;
    }
    else
    {
        n->next = s->top;
        s->top = n;
    }
}

float pop(stack* s)
{
    if (s->top)
    {
        float x = s->top->data;
        node* temp = s->top;
        s->top = s->top->next;
        free(temp);
        return x;
    }

}

float evaluate(char c, float x, float y)
{
    switch (c)
    {
    case '*':
        return x * y;
    case '/':
        return x / y;
    case '%':
        return fmod(x, y);
    case '+':
        return x + y;
    case '-':
        return x - y;
    case '^':
        return pow(x, y);
    default:
        return 0;
    }
}

float evaluatePostfix(char* postfix)
{
    char* tok;
    float a, b, result, num;
    stack* s = initialize();
    tok = strtok(postfix, " ");

    while (tok)
    {
        if (isdigit(tok[0]))
        {
            num = atof(tok);
            push(s, num);
        }
        else
        {
            a = pop(s);
            b = pop(s);
            result = evaluate(tok[0], b, a);
            push(s, result);
        }
        tok = strtok(NULL, " ");
    }

    result = pop(s);
    return result;
}

int main()
{
    char exp []= "10 3 5 * 16 4 - / +";
    float res = evaluatePostfix(exp);
    printf("%f\n", res);
    return 0;
}
