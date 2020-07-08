#include<stdio.h>
#include<string.h>
char str1[10][7],str2[10][7];
int checkssn(char var[])
{
    int j;
    for(j=1;j<=9;j++)
    {

       if(strcmp(str1[j],var)==0)
       {
           strtok(str2[j],"\n");
           j=atoi(str2[j]);
           return j;
       }

    }
    return 0;
}
int main()
{
	char ssntab[4][10],var[10][256],var1[4][10],str[10][50],mnt1[10],mnt2[8],mnt3[10];
	char kp[3][5];
	char delim[2]=" ";
	char *ptr;
	int sstab[5],mec[50];
	int i,j=1,m=0,n=0,x=0,l=1,flag=0,flag1=0,ssn,end=0,b;
	FILE *f1,*f2,*f3,*f4;
	f1=fopen("macro ip.txt","r");
	f2=fopen("macro ip2.txt","r");
	f3=fopen("kpdtab.txt","r");
	f4=fopen("macro call.txt","r");
	fscanf(f4,"%s%s%d",mnt1,mnt2,&b);
	for(l=1;l<9;l++)
    {
        fscanf(f2,"%s%s",str1[l],str2[l]);
    }
    for(l=1;l<2;l++)
    {
        fscanf(f3,"%s%s",kp[l],kp[l+1]);
        //printf("%s\t%s\n",kp[l],kp[l+1]);
    }
	if(strcmp(str1[1],mnt1)!=0)
    {
        while(!feof(f1))
        {
            static int j=1;
            fgets(var,sizeof(var),f1);
            strcpy(str[j],var);
            j++;
        }
        j=1;
        while(j<8)
        {
            i=0;
            strcpy(var,str[j]);
            ptr=strtok(var,delim);
            while(ptr!=NULL)
            {
                strcpy(*(var1+i),ptr);
                i++;
                ptr=strtok(NULL,delim);
            }
            if(strcmp(var1+0,"LCL")==0)
            {
                mec[x]=1;
                x++;
            }
            if(strcmp(var1+1,"SET")==0)
            {

                mec[x]=2;
                if(strcmp(var1+2,"0")==0)
                    m=0;
                else if(strcmp(var1+4,"1\n")==0)
                {
                    mec[x]=5;
                    m=m+1;
                    //printf("%d\n",m);
                }
                x++;
            }
            if(strcmp(var1+0,"MOVER")==0)
            {

                mec[x]=3;
                x++;
                ptr=strtok(var1+1,",");
                ptr=strtok(NULL," ");
                if(strcmp(ptr,"3")==0)
                {
                    printf("+MOVER %s,%d\n",kp[2],m);
                }

            }
            if(strcmp(var1+0,"MOVEM")==0)
            {

                mec[x]=4;
                x++;
                ptr=strtok(var1+1,",");
                ptr=strtok(NULL," ");
                if(strcmp(ptr,"3")==0)
                {
                    ptr=strtok(var1+3,",");
                    ptr=strtok(NULL," ");

                    if(strcmp(ptr,"1")==0)
                    {
                        ptr=strtok(var1+5,",");
                        if(strcmp(ptr,"E")==0)
                            printf("+MOVEM %s,%s+%d\n",kp[2],mnt2,m);
                    }
                }
            }
            if(strcmp(var1+0,"AIF")==0)
            {
                mec[x]=6;
                x++;

                ptr=strtok(var1+3,",");
                ptr=strtok(NULL," ");
                if(strcmp(ptr,"2")==0)
                {
                   if(m<b)
                   {
                        end=1;
                        l++;
                        //break;
                   }
                   else
                   {
                       end=0;
                   }
                }
            }
            //printf("%d\n",end);
            if(end==0)
                j++;
            else if(end==1)
            {
                ssn=checkssn("sstp");
                j=ssn;
                end=0;
            }
        }
	}
	else
        return 0;
    //printf("%s",var[1]);
}
