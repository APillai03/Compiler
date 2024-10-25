#include"Follow.h"
typedef struct
{
    char itemprod[100][100];
    int dotpos[100];
    int transition[255];
}items;
items item_arr[100];
void item0()
{
    items i0;
    for(int i=0;i<100;i++)
    {
        memset(i0.itemprod[i],0,100);
        
    }
    memset(i0.dotpos,-1,sizeof(i0.dotpos));
    memset(i0.transition,-1,sizeof(i0.transition));

    char temp[4];
    temp[0] = 'Q';
    temp[1] = '=';
    temp[2] = Prod[0][0];
    temp[3] = '\0';
    strcat(i0.itemprod[0],temp);
    i0.dotpos[0]=2;
        
}
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
    item0();
}