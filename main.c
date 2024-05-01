#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
/// PART1: stack implementation using linkedlist
// first->chars stack
typedef struct
{
    char data1;
    struct node1 *next1;
} node1;
typedef struct
{
    node1 *top1;
} stack1;
stack1 *initialize1()
{
    stack1 *s = malloc(sizeof(stack1));
    s->top1 = NULL;
    return s;
}
node1 *newnode1(char x)
{
    node1 *n = malloc(sizeof(node1));
    n->data1 = x;
    n->next1 = NULL;
    return n;
}
int isEmpty1(stack1 *s)
{
    if (s->top1 == NULL)
        return 1;
    else
        return 0;
}
void push1(stack1 *s, char x)
{
    node1 *n = newnode1(x);
    if (isEmpty1(s))
    {
        s->top1 = n;
    }
    else
    {
        n->next1 = s->top1;
        s->top1 = n;
    }
}
char pop1(stack1 *s)
{
    if (!isEmpty1(s))
    {
        char x = s->top1->data1;
        node1 *temp = s->top1;
        s->top1 = s->top1->next1;
        free(temp);
        return (x);
    }
}
char top1(stack1 *s)
{
    if (!isEmpty1(s))
    {
        return (s->top1->data1);
    }
}
// Second: Float stack
typedef struct node
{
    float data;
    struct node *next;
} node;

typedef struct
{
    node *top;
} stack;

stack *initialize()
{
    stack *s = malloc(sizeof(stack));
    s->top = NULL;
    return s;
}

node *newnode(float x)
{
    node *n = malloc(sizeof(node));
    n->data = x;
    n->next = NULL;
    return n;
}

int isEmpty(stack *s)
{
    return s->top == NULL;
}

void push(stack *s, float x)
{
    node *n = newnode(x);
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

float pop(stack *s)
{
    if (s->top)
    {
        float x = s->top->data;
        node *temp = s->top;
        s->top = s->top->next;
        free(temp);
        return x;
    }
}
/// TASK2:Convertion
int priority(char x)
{
    if (x == '^')
        return 3;
    else if (x == '*' || x == '%' || x == '/')
        return 2;
    else if (x == '-' || x == '+' || x == '–')
        return 1;
    else
        return 0;
}
char *infixToPostfix(char *infix)
{
    char *postfix = malloc(2 * strlen(infix) + 1);
    char ss[strlen(infix) + 1];
    strcpy(ss, infix);
    char *op = strtok(ss, " ");
    int count = 0;
    stack1 *s = initialize1();
    while (op != NULL)
    {
        if (isdigit(op[0]))
        {
            int i = 0;
            while (op[i] != '\0')
            {
                postfix[count++] = op[i++];
            }
            postfix[count++] = ' ';
        }
        else if (op[0] == ')')
        {
            while (!isEmpty1(s) && top1(s) != '(')
            {
                postfix[count++] = pop1(s);
                postfix[count++] = ' ';
            }

            if (!isEmpty1(s) && top1(s) == '(')
            {
                pop1(s);
            }
        }
        else
        {
            while (!isEmpty1(s) && priority(op[0]) <= priority(top1(s)) && top1(s) != '(')
            {
                postfix[count++] = pop1(s);
                postfix[count++] = ' ';
            }
            push1(s, op[0]);
        }
        op = strtok(NULL, " ");
    }
    while (!isEmpty1(s))
        postfix[count++] = pop1(s);
    postfix[count] = '\0';
    free(s);
    return postfix;
}
/// TASK3: Evaluation the exp
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

float evaluatePostfix(char *postfix)
{
    char *tok;
    float a, b, result, num;
    stack *s = initialize();
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
    char exp[] = "10 3 5 * 16 4 - / +";
    float res = evaluatePostfix(exp);
    printf("%f\n", res);
    return 0;
}
