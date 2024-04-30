#include <stdio.h>
#include <stdlib.h>
///Part 1: stack implementation using linkedlist
typedef struct
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
    stack* s= malloc (sizeof (stack));
    s->top=NULL;
    return s;
}
node* newnode(float x)
{
    node*n=malloc(sizeof(node));
    n->data=x;
    n->next=NULL;
    return n;
}
int isEmpty(stack*s)
{
    if(s->top==NULL)
        return 1;
    else return 0;
}
node* push(stack *s,float x)
{
    node*n=newnode(x);
    if(isEmpty(s))
    {
        s->top=n;
    }
    else
    {
        n->next=s->top;
        s->top=n;
    }
}
float pop(stack *s)
{
   if(s->top){
    float x= s->top->data;
    node*temp=s->top;
    s->top=s->top->next;
    free(temp);
   }
}
int main()
{
    ///Testing part one
    stack*s=initialize();
    printf("%d\n",isEmpty(s));
    push(s,5.6);
    printf("%d\n",isEmpty(s));
    push(s,10.5);
    printf("%f\n",pop(s));
    printf("%f\n",pop(s));
    printf("%f\n",pop(s));
    free(s);
    ///
}
