#include<stdio.h>
#include<string.h>
char pntab [4][5], evtab [3][3], kpdtab [3][5], ssntab [2][5];
int pn, pn1, ev, ssn;  
int checkpn (char var [])
{
    int j; 
    for(j=1;j<=5;j++)
    {
       // printf("%s\n",var);
       if(strcmp(pntab[j],var)==0)
         return j;
    }
    return 0;
}
int checkev(char var[])
{
    int j;
    for(j=1;j<=3;j++)
    {
        strtok(var,"\n");
        //printf("%s\n",var);
       if(strcmp(evtab[j],var)==0)
         return j;
    }
    return 0;
}
int checkssn(char var[])
{
    int j;
    for(j=1;j<=3;j++)
    {
        strtok(var,"\n");
        //printf("%s\n",var);
       if(strcmp(ssntab[j],var)==0)
         return j;
    }
    return 0;
}
main()
{
    char var[256],var1[7][10],mnt[10];
	char delim[2]=" ";
	char *ptr;
	int i,m=1,n=1,pp=0,kp=0,ev2=0,mdtp,kpdtp,sstp,l=0;
	FILE *f1,*f2,*f3,*f4;
	f1=fopen("macro def.txt","r");
	f2=fopen("macro ip.txt","w");
	f3=fopen("macro ip2.txt","w");
	f4=fopen("kpdtab.txt","w");
    while(!feof(f1))
    {
        fgets(var,sizeof(var),f1);
        ptr=strtok(var,delim);
        i=0;
        while(ptr!=NULL)
        {
            strcpy(*(var1+i),ptr);
            i++;
            ptr=strtok(NULL,delim);
        }
        if(strcmp(var1+0,"MACRO\n")==0)
        {
        }
        else if(strcmp(var1+0,"LCL")==0)
        {
            m=1;
            ev2++;
            strtok(var1+1,"\n");
            ptr=strtok(var1+1,"&");
            strcpy(*(evtab+m),ptr);
            ev=checkev(ptr);
            printf("%s E,%d\n",var1+0,ev);
            fprintf(f2,"%s E,%d\n",var1+0,ev);
            l++;
            mdtp=l;
        }
        else if(strcmp(var1+1,"SET")==0)
        {
            ptr=strtok(var1+0,"&");
            ev=checkev(ptr);
            //printf("%s\n",ptr);
            if(strcmp(var1+2,"0\n")==0)
            {
                printf("E,%d SET 0\n",ev,var1+0);
                fprintf(f2,"E,%d SET 0\n",ev,var1+0);
            }

            else
            {
                printf("E,%d %s E,%d %s %s",ev,var1+1,ev,var1+3,var1+4);
                fprintf(f2,"E,%d %s E,%d %s %s",ev,var1+1,ev,var1+3,var1+4);
            }
            l++;
        }
        else if(strcmp(var1+0,"MOVER")==0)
        {
            ptr=strtok(var1+1,"&");
            pn=checkpn(ptr);
            ptr=strtok(var1+3,"&");
            ev=checkev(ptr);
            printf("%s P,%d , E,%d\n",var1+0,pn,ev);
            fprintf(f2,"%s P,%d , E,%d\n",var1+0,pn,ev);
            l++;
        }
        else if(strcmp(var1+1,"MOVEM")==0)
        {
            m=1;
            ptr=strtok(var1+0,".");
            strcpy(*(ssntab+m),ptr);
            ptr=strtok(var1+2,"&");
            pn=checkpn(ptr);
            ptr=strtok(var1+4,"&");
            pn1=checkpn(ptr);
            ptr=strtok(var1+6,"&");
            ev=checkev(ptr);
            printf("%s P,%d , P,%d %s E,%d\n",var1+1,pn,pn1,var1+5,ev);
            fprintf(f2,"%s P,%d , P,%d %s E,%d\n",var1+1,pn,pn1,var1+5,ev);
            l++;
            sstp=l;
        }
        else if(strcmp(var1+0,"AIF")==0)
        {
            ptr=strtok(var1+1,"&");
            ev=checkev(ptr);
            ptr=strtok(var1+3,"&");
            pn=checkpn(ptr);
            strtok(var1+4,"\n");
            ptr=strtok(var1+4,".");
            ssn=checkssn(ptr);
            printf("%s E,%d %s P,%d S,%d\n",var1+0,ev,var1+2,pn,ssn);
            fprintf(f2,"%s E,%d %s P,%d S,%d\n",var1+0,ev,var1+2,pn,ssn);
            l++;
        }
        else if(strcmp(var1+0,"MEND")==0)
        {
            printf("%s\n",var1+0);
            fprintf(f2,"%s",var1+0);
            l++;
        }
        else if(strcmp(var1+0,"MACRO")!=0)
        {
            strcpy(mnt,var1+0);
            for(i=1;i<7;i=i+1)
            {
                if(strcmp(var1+i,",")==0)
                    continue;
                if(strcmp(var1+i,"=")==0)
                {
                    ptr=strtok(var1+(i-1),"&");
                    strcpy(*(kpdtab+n),ptr);
                    //printf("%s\n",kpdtab+n);
                    n++;
                    strcpy(*(kpdtab+n),var1+(i+1));
                    kp++;
                    kpdtp=kp;
                    //printf("%s\n",kpdtab+n);
                    continue;
                }
                ptr=strtok(var1+i,"&");
                strcpy(*(pntab+m),ptr);
                //
                m++;
                pp++;
            }
            pp=pp-kp;
            //printf("%d  %d\n",pp,kp);
        }
    }
    printf("pp:%d  kp:%d ev:%d kpdtp:%d sstp:%d\n",pp,kp,ev,mdtp,sstp);
    fprintf(f3,"%s 00\npp %d\nkp %d\nev %d\nmdtp %d\nkpdtp %d\nsstp %d\n",mnt,pp,kp,ev,mdtp,kpdtp,sstp);
    fprintf(f4,"%s %s",kpdtab[1],kpdtab[2]);
}
