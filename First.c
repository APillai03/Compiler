#include"First.h"
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
    traverser1();
    for(int i=0;i<26;i++)
    {
        if(First[i][0]!=0)
        {
            printf("First of %c->%s\n",i+65,First[i]);
        }
        
    }

    return 0;
}