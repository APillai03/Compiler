#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
char Prod[26][26];
char First[26][26];
int n;
void inserter(char* arr, char ch)
{
    int is_present=0;
    for(int i=0;i<strlen(arr);i++)
    {
        if(arr[i]==ch)
        {
            is_present=1;
        }
    }
    if(!is_present)
    {
        char temp[2];
        temp[0]=ch;
        temp[1]='\0';
        strcat(arr,temp);
    }
}
void calc_first(char non_term)
{
    for(int i=0;i<n;i++)
    {
        if(Prod[i][0]==non_term)
        {
            if(!isupper(Prod[i][2]) || Prod[i][2]=='#')
            {
                inserter(First[non_term-65],Prod[i][2]);
            }
            else
            {
                for(int j=2;j<strlen(Prod[i]);j++)
                {
                    if(isupper(Prod[i][j]) && Prod[i][j]!=non_term)
                    {
                        calc_first(Prod[i][j]);
                    }
                    else if(isupper(Prod[i][j]) && Prod[i][j]==non_term)
                    {
                        continue;
                    }
                    else
                    {
                        break;
                    }
        
                    
                }
                int contains_epsilon=1;
                int count=0;
                int check = strlen(Prod[i]);
                for(int j=2;j<strlen(Prod[i]) && contains_epsilon;j++)
                {
                    //printf("This->%s\n", Prod[i]);
                    int flag=0;
                    
                    if(!isupper(Prod[i][j]))
                    {
                        inserter(First[non_term-65],Prod[i][j]);
                        
                    }
                    for(int k=0;k<strlen(First[Prod[i][j]-65]);k++)
                    {
                        //printf("%d\n",strlen(First[Prod[i][j]-65]));
                        if(First[Prod[i][j]-65][k]=='#')
                        {
                            flag=1;
                        }
                        else
                        {
                            inserter(First[non_term-65],First[Prod[i][j]-65][k]);
                        }
                    }
                    if(flag)
                    {
                        contains_epsilon=1;
                        count+=1;
                    }
                    else
                    {
                        contains_epsilon=0;
                    }
                }
                if(count==strlen(Prod[i])-2)
                {
                    inserter(First[non_term-65],'#');
                }
            }
        }
    }
    return ;
}
void traverser1()
{
    for(int i=0;i<n;i++)
    {
        calc_first(Prod[i][0]);
    }
}