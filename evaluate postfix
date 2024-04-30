#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float evaluate (char c, float x, float y)
{
    switch(c)
    {
    case '*':
        return x*y;
    case '/':
        return x/y;
     case '%':
            return fmod(x,y);
    case '+':
        return x+y;
    case '-':
        return x-y;
    case '^':
        return pow(x,y);
    default:
        return;

    }
}
float evaluatePostfix (char*postfix)
{


    float a,b,result;
    stack *s= initialize();
    for(int i=0; i<strlen(postfix); i++)
    {
        if(isdigit(postfix[i]))
            push(s,postfix[i]-'0');

        else
        {
            a=pop(s);
            b=pop(s);
            result= evaluate(postfix[i],b,a);
            push(s,result);
        }
    }
    result=pop(s);
    return result;

}
int main()
{

    char *exp=" 124*+3+";
    float res=evaluatePostfix(exp);
    printf("%f",res);


}


