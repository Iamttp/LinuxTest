/***************************************************
 * ls命令首先
 * 类似于who.cpp读取struct utmp，这里读取dirent.h中的struct dirent
 * 
 * 输出的目标：
 *      printf，是把格式字符串输出到标准输出（一般是屏幕，可以重定向）；
 *      fprintf，是把格式字符串输出到指定文件设备中，所以参数笔printf多一个文件指针FILE*。
 * 
 * 
***************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void do_ls(char[]);

int main(int argc, char *argv[])
{
    if (argc == 1)
        do_ls(".");
    else
    {
        while (--argc)
        {
            printf("%s:\n", *++argv);
            do_ls(*argv);
        }
    }
    return 0;
}

void do_ls(char dirname[])
{
    DIR *dir_ptr;
    struct dirent *direntp;

    if((dir_ptr=opendir(dirname))==NULL)
        fprintf(stderr,"can't open %s\n",&dirname);
    else
    {
        while((direntp=readdir(dir_ptr))!=NULL)
            printf("%s\n",direntp->d_name);
        closedir(dir_ptr);
    }
}