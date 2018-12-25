/***************************************************
    * more实现（暂时存在部分缺陷）
    * 关键字    ： argc,argv
    *          : fgets(line,LINELEN,fp)
    *          : fputs(line,stdout)
    *          : \033[7m printf反显 
***************************************************/

#include<stdio.h>
#include<stdlib.h>

void do_more(FILE*);
int see_more();

//无参数argc==1
int main(int argc, char const *argv[])
{
    FILE *fp;
    if(argc==1)
    {
        //printf("%s\n",argv[0]);
        do_more(stdin);
    }
    else
    {
        while(--argc)
        {
            if((fp=fopen(*++argv,"r"))!=NULL)
            {
                do_more(fp);
                fclose(fp);
            }
            else
                exit(1);
        }
    }
    return 0;
}

#define LINELEN 512
#define PAGELEN 24 
void do_more(FILE *fp)
{
    char line[LINELEN];
    int num_of_line=0;
    int reply;
    //读取每一行赋值给line
    while(fgets(line,LINELEN,fp))
    {
        
        if (num_of_line==PAGELEN) {     //满屏
            reply=see_more();
            if(reply==0)
                break;
            num_of_line-=reply;
        }
        if(fputs(line,stdout)==EOF)     //打印
            exit(1);
        num_of_line++;
    }
}

int see_more()
{
    int c;
    printf("\033[7m more? \033[0m");
    c=getchar();
    if(c!=EOF){
        if(c=='q')
            return 0;
        if(c=='m')
            return PAGELEN;
        if(c=='\n')
            return 1;
    }
    return 0;
    
}