#include"First.h"
char Follow[26][26];

void calcFollow(char symbol)
{
    for(int i=0;i<n;i++)
    {
        if(Prod[i][0]==symbol)
        {
            if(i==0)          //Checks if symbol is start symbol
            {
                inserter(Follow[symbol-65],'$');
            }

            for(int st=0;st<n;st++)
            {
                for(int j=2;j<26;j++)
                {
                    if(Prod[st][j]==symbol)
                    {
                        int count=j;
                       // printf("%c->%c %d %d",symbol,Prod[st][0],j,strlen(Prod[st]));
                        if(j==strlen(Prod[st])-1 && Prod[st][0] != symbol)
                        {
                           // printf("%s", Follow[Prod[st][0]-65]);
                            for(int x=0;x<strlen(Follow[Prod[st][0]-65]);x++)
                            {
                                inserter(Follow[symbol-65],Follow[Prod[st][0]-65][x]);
                            }
                            break;
                        }
                        for(int k=j+1;k<strlen(Prod[st]);k++)
                        {
                            if(!isupper(Prod[st][k]) && Prod[st][k]!='#')
                            {
                                inserter(Follow[symbol-65],Prod[st][k]);
                                break;
                            }
                            else
                            {
                                int contains_epsilon=0;
                                for(int w=0;w<strlen(First[Prod[st][k]-65]);w++)
                                {
                                    if(First[Prod[st][k]-65][w]=='#')
                                    {
                                        contains_epsilon=1;
                                        count+=1;
                                    }
                                }
                                for(int x=0;x<strlen(First[Prod[st][k]-65]);x++)
                                {
                                    if(First[Prod[st][k]-65][x]!='#')
                                    {
                                        inserter(Follow[symbol-65],First[Prod[st][k]-65][x]);
                                    }
                                    
                                }
                                
                                if(!contains_epsilon)
                                {
                                    break;
                                }
                            }
                        }
                        if(count==strlen(Prod[st])-1 && Prod[st][0] != symbol)
                        {
                            for(int x=0;x<strlen(Follow[Prod[st][0]-65]);x++)
                            {
                                inserter(Follow[symbol-65],Follow[Prod[st][0]-65][x]);
                            }
                        }
                        
                    }
                }
            }
            
            
        }
        
    }
    
}

void traverser2()
{
    for(int i=0;i<n;i++)
    {
        calcFollow(Prod[i][0]);
    }
}