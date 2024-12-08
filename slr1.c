#include"Follow.h"
#include<stdbool.h>
typedef struct
{
    char itemprod[100][100];
    int dotpos[100];
    int transition[255];
    int red;
}items;
items item_arr[100];
int item_no = 0;
int parsing_table[100][255] = {0};
int check_duplicate(items item)
{
    for(int i=0;i<item_no+1;i++)
    {
        if(strcmp(item_arr[i].itemprod[0],item.itemprod[0])==0 && item_arr[i].dotpos[0]==item.dotpos[0])
        {
            return i;
        }
    }
    return -1;
}
void transition(int it)
{
    
    for(int i=0;item_arr[it].dotpos[i]!=-1;i++)
    {
        if(item_arr[it].dotpos[i]==strlen(item_arr[it].itemprod[i]))
        {
            return;
        }
        int x = item_arr[it].transition[item_arr[it].itemprod[i][item_arr[it].dotpos[i]]];
        
        if(x==-1)
        {
            int prod=-1;
            items a;
            for(int j=0;j<100;j++)
            {
                memset(a.itemprod[j],0,100);

            }
            memset(a.dotpos,-1,sizeof(a.dotpos));
            memset(a.transition,-1,sizeof(a.transition));
            

            char sym = item_arr[it].itemprod[i][item_arr[it].dotpos[i]];

            for(int j=0;item_arr[it].dotpos[j]!=-1;j++)
            {
                if(item_arr[it].itemprod[j][item_arr[it].dotpos[j]]==sym)
                {
                    strcat(a.itemprod[++prod],item_arr[it].itemprod[j]);
                    a.dotpos[prod] = item_arr[it].dotpos[j] + 1;
                }
            }

            int ind = check_duplicate(a);
            if(ind==-1)
            {
                item_no+=1;
                item_arr[item_no] = a;
                item_arr[it].transition[item_arr[it].itemprod[i][item_arr[it].dotpos[i]]] = item_no;

            }
            else
            {
                item_arr[it].transition[item_arr[it].itemprod[i][item_arr[it].dotpos[i]]] = ind;
            }
            
            
        }

    }
    
}
void productiongen(int it)
{
    char nonterms[20];
    memset(nonterms,0,20);
    if(item_arr[it].itemprod[0][item_arr[it].dotpos[0]]==0)
    {
        //printf("HELLo");
        return;
    }
    nonterms[0] = item_arr[it].itemprod[0][item_arr[it].dotpos[0]];
    int ptr=0;
    int qtr=0;
    for(int j=0;nonterms[j]!='\0';j++)
    {
        for(int i=0; i<n; i++)
        {
            if(nonterms[j]==Prod[i][0])
            {
                strcat(item_arr[it].itemprod[++qtr],Prod[i]);
                if(nonterms[j]!=Prod[i][2] && isupper(Prod[i][2]))
                {
                    nonterms[++ptr] = Prod[i][2];                
                }
                item_arr[it].dotpos[qtr]= 2;
            }
        }
    }
    
    
    transition(it);
    
    
    
}
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
    item_arr[0] = i0;
    productiongen(0);
        
}
void update_table()
{
    parsing_table[1]['$'] = -1;
    for(int i=0;i<item_no+1;i++)
    {
        
        int count=0;
        for(int j=0;j<255;j++)
        {
            if(item_arr[i].transition[j]!=-1)
            {
                if(!isupper(j))
                {
                    parsing_table[i][j] = item_arr[i].transition[j];
                }
                else
                {
                    parsing_table[i][j] = item_arr[i].transition[j];
                }
            }
            else
            {
                count+=1;
            }
        }
        if(count==255)
        {
            if(i!=1)
            {
                item_arr[i].red = 1;
            }
            
        }
        else
        {
            item_arr[i].red = 0;
        }

    }
    for(int i=0;i<item_no+1;i++)
    {
        if(item_arr[i].red==1)
        {
            for(int j=0;j<n;j++)
            {
                if(strcmp(item_arr[i].itemprod[0],Prod[j])==0)
                {
                    for(int k=0;Follow[Prod[j][0]-65][k]!='\0';k++)
                    {
                        parsing_table[i][Follow[Prod[j][0]-65][k]] = j+1;
                    }
                }
            }
        }
    }
}
void parser(char* str)
{
    int top = -1;
    int ptr=0;
    char stack[100];
    memset(stack,0,100);

    stack[++top] = '$';
    stack[++top] = '0';

    int c=0;
    while(c<100)
    {
        if(str[ptr]=='$' && stack[top]=='1')
        {
            printf("%s\n",stack);
            printf("YES");
            break;
        }
        else if(parsing_table[stack[top]-48][str[ptr]]==0)
        {
            printf("NO");
            break;
        }
        else
        {
            int it_no = stack[top]-48;
            if(item_arr[it_no].red!=1)
            {
                stack[++top] = str[ptr];
                stack[++top] = parsing_table[it_no][str[ptr]] + '0';
                ptr++;
            }
            else
            {
                int pops = (strlen(Prod[parsing_table[it_no][str[ptr]]-1])-2)*2;
                pops = (pops==0 )* 1 + (pops!=0)*pops;
                for(int i=0;i<pops;i++)
                {
                    top = top-1;
                }
                stack[++top] = Prod[parsing_table[it_no][str[ptr]]-1][0];
                char a = stack[top-1];
                char b = stack[top];
                stack[++top] = parsing_table[a-48][b] + '0';
            }
        }
        c++;
    }

}
int main()
{
    while(1)
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
    for(int i=1;i<9;i++)
    {
        productiongen(i);
        
    }

    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            printf("%s-%d\t",item_arr[i].itemprod[j],item_arr[i].dotpos[j]);
        }
        printf("\n");
    }
    for(int i=0;i<item_no+1;i++)
    {
        for(int j=0;j<255;j++)
        {
            if(item_arr[i].transition[j]!=-1)
            {
                printf("%d->%c=%d\n",i,j,item_arr[i].transition[j]);
            }
        }
    }
    update_table();
    for(int i=0;i<item_no+1;i++)
    {
        printf("\n%d ",i);
        for(int j=0;j<255;j++)
        {
            if(parsing_table[i][j]!=0)
            {
                printf(" %c->%d ",j,parsing_table[i][j]);
            }
        }
        printf("\n");
    }
    char* str;
    scanf("%s",str);
    parser(str);
    }
    
}