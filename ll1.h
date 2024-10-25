#include"Follow.h"
#include<stdbool.h>
int Table[26][256];
void tablegen()
{
    for(int i=0; i<26; i++)
    {
        memset(Table[i], -1, sizeof(Table[i]));
    }
    for(int i=0;i<n;i++)
    {
        int contains_epsilon=0;
        for(int j=0; j<strlen(First[Prod[i][0]-65]);j++)
        {
            if(First[Prod[i][0]-65][j]=='#')
            {
                contains_epsilon=1;
            }
            else
            {
                int check=1;
                int count=2;
                for(int k=2;k<strlen(Prod[i]) && check;k++)
                {
                    if(!isupper(Prod[i][k]) && Prod[i][k]!='#')
                    {
                        Table[Prod[i][0]-65][Prod[i][k]] = i;
                        break;
                    }
                    else
                    {
                        check=0;
                        for(int l=0;l<strlen(First[Prod[i][k]-65]);l++)
                        {
                            if(!isupper(First[Prod[i][k]-65][l]) && First[Prod[i][k]-65][l] != '#')
                            {
                                Table[Prod[i][0]-65][First[Prod[i][k]-65][l]]=i;
                            }
                            else if(First[Prod[i][k]-65][l] == '#')
                            {
                                check=1;
                                count++;
                            }
                        }
                    }
                }
                if(count==strlen(Prod[i]))
                {
                    contains_epsilon=1;
                }
                
            }
        }
        if(contains_epsilon)
        {
            for(int j=0; j<strlen(Follow[Prod[i][0]-65]);j++)
            {
                for(int k=0;k<n;k++)
                {
                    if(Prod[k][0]==Prod[i][0]  && Prod[k][2]=='#')
                    {
                        Table[Prod[i][0]-65][Follow[Prod[i][0]-65][j]] = k;
                        break;
                    }
                }
                
            }
        }
    }

    for(int i=0;i<26;i++)
    {
        for(int j=0;j<256;j++)
        {
            if(Table[i][j]>-1)
            {
                printf("%c on %c is %s\n",i+65,j,Prod[Table[i][j]]);
            }
            
        }

    }
    return; 
}
bool Parser(char* expression)
{
    int ptr=0;
    char stack[100];
    memset(stack,0,100);
    int top=-1;
    stack[++top] = '$';
    stack[++top] = Prod[0][0];
    while(ptr<strlen(expression))
    {
        
        if(!isupper(stack[top]))
        {
            if(expression[ptr]=='$')
            {
                if(stack[top]=='$')
                {
                    return true;
                }
            }
            if(expression[ptr]==stack[top])
            {

                ptr++;
                top--;

            }
            else if(stack[top]=='#')
            {
                //printf("%c\n",stack[top]);
                top--;
            }
            else
            {
                return 0;
            }    
        }
        
        else
        {
            // printf("%c",Prod[0][2]);
            
            char x = stack[top];
            
            top--;
            if(Table[x-65][expression[ptr]]==-1)
            {
                return false;
            }
            for(int j=strlen(Prod[Table[x-65][expression[ptr]]])-1;j>1;j--)
            {
            
                if(Table[x-65][expression[ptr]]==-1)
                {
                    return false;
                }
                stack[++top] = Prod[Table[x-65][expression[ptr]]][j];
                
            }
            

            
            
        }
        //printf("%s\n",stack);
        
        
    }
    return false;

}