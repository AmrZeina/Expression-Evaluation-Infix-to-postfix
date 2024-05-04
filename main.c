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
    switch (x)
    {
    case '(':
        return 4;
    case '^':
        return 3;
    case '*':
    case '%':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    }
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
        if (isdigit(op[0]) || (op[0] == '-' && isdigit(op[1])))
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
    {
        postfix[count++] = pop1(s);
        postfix[count++] = ' ';
    }
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
        if (isdigit(tok[0]) || (tok[0] == '-' && isdigit(tok[1])))
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
    free(s);
    return result;
}
int main()
{
    char exp1[] = " 1 + 2 * 4 + 3 ";
    printf(" Input (Infix): %s\nOutput (Postfix): %s\nValue: %f\n\n", exp1, infixToPostfix(exp1), evaluatePostfix(infixToPostfix(exp1)));
    char exp2[] = " ( 1 + 2 ) * 4 + 3";
    printf(" Input (Infix): %s\nOutput (Postfix): %s\nValue: %f\n\n", exp2, infixToPostfix(exp2), evaluatePostfix(infixToPostfix(exp2)));
    char exp3[] = "10 + 3 * 5 / ( 16 - 4 )";
    printf(" Input (Infix): %s\nOutput (Postfix): %s\nValue: %f\n\n", exp3, infixToPostfix(exp3), evaluatePostfix(infixToPostfix(exp3)));
    char exp4[] = "2 + 3 * 4 ";
    printf(" Input (Infix): %s\nOutput (Postfix): %s\nValue: %f\n\n", exp4, infixToPostfix(exp4), evaluatePostfix(infixToPostfix(exp4)));
    char exp5[] = "2 + ( -2.5 + 3.14 ) * ( -5.4 + 8.1 ) ^ ( -0.5 ) ";
    printf(" Input (Infix): %s\nOutput (Postfix): %s\nValue: %f\n\n", exp5, infixToPostfix(exp5), evaluatePostfix(infixToPostfix(exp5)));
    return 0;
}
