/***************************************************
    * more实现（暂时存在部分缺陷）
    * 关键字    ： argc,argv
    *          : fgets(line,LINELEN,fp)
                    函数原型
                        char *fgets(char *buf, int bufsize, FILE *stream);
                    参数
                        *buf: 字符型指针，指向用来存储所得数据的地址。
                        bufsize: 整型数据，指明存储数据的大小。
                        *stream: 文件结构体指针，将要读取的文件流。
    *          : fputs(line,stdout)         
                        int fputs(const char *str, FILE *stream);
                    返回值：该函数返回一个非负值，如果发生错误则返回 EOF(-1)。
                        （1）str：这是一个数组，包含了要写入的以空字符终止的字符序列。
                        （2）stream：指向 FILE 对象的指针，该 FILE 对象标识了要被写入字符串的流
    *          : \033[7m                    printf反显 
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