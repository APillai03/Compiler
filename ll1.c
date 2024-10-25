#include"ll1.h"
int main()
{
    printf("Enter the no of Productions: ");
    scanf("%d", &n);
    printf("Enter the Grammar e.g. A=aB: \n");
    for(int i=0;i<n;i++)
    {
        memset(Prod[i],0,26);
        scanf("%s", Prod[i]);
    }
    for(int i=0;i<26;i++)
    {
        memset(First[i],0,26);
    }
    for(int i=0;i<26;i++)
    {
        memset(Follow[i],0,26);
    }
    traverser1();
    traverser2();
    tablegen();
    char expression[100];
    memset(expression,0,100);
    printf("Enter the expression to parse(End with $):\n");

    scanf("%s",expression);
    if(Parser(expression))
    {
        printf("ACCEPTED");
    }
    else
    {
        printf("REJECTED");
    }

    return 0;
}