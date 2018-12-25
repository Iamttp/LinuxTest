/***************************************************
 * who命令实现
 * ****************************************
 * 关键字：fopen(UTMP_FILE, "r")
        函数原型：
            FILE * fopen(const char * path, const char * mode);
        返回值：
            文件顺利打开后，指向该流的文件指针就会被返回。如果文件打开失败则返回 NULL，并把错误代码存在error中。
            一般而言，打开文件后会做一些文件读取或写入的动作，若打开文件失败，
            接下来的读写动作也无法顺利进行，所以一般在 fopen() 后作错误判断及处理。
 * ****************************************
 *      ：fread(&current_record, sizeof(char), reclen, utmpfd)
        函数原型
            size_t fread ( void *buffer, size_t size, size_t count, FILE *stream) ;
        参 数
            buffer 用于接收数据的内存地址
            size 要读的每个数据项的字节数，单位是字节
            count 要读count个数据项，每个数据项size个字节.
            stream 输入流
        返回值
            返回真实读取的项数，若大于count则意味着产生了错误。
            另外，产生错误后，文件位置指示器是无法确定的。若其他stream或buffer为空指针，
            或在unicode模式中写入的字节数为奇数，此函数设置errno为EINVAL以及返回0.
 * ****************************************
 *      ：fclose(utmpfd)
 *  struct utmp
    {
        short int ut_type; // 登录类型
        pid_t ut_pid; // login进程的pid
        char ut_line[UT_LINE_SIZE]; // 登录装置名，省略了"/dev/"
        char ut_id[4]; // Inittab ID
        char ut_user[UT_NAMESIZE]; // 登录账号
        char ut_host[UT_HOSTSIZE]; // 登录账号的远程主机名称
        struct exit_status ut_exit; // 当类型为DEAD_PROCESS时进程的结束状态
        long int ut_session; // SessionID
        struct timeval ut_tv; // 时间记录
        int32_t ut_addr_v6[4]; // 远程主机的网络地址
        char __unused[20]; // 保留未使用
    };
 * 
***************************************************/
#include <stdio.h>
#include <utmp.h> //usr/include/utmp.h
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define SHOWHOST

void show_info(struct utmp *utmpfp)
{
    /* 根据当前用户的状态值，判断是否为当前登录用户 */
    if (utmpfp->ut_type == USER_PROCESS)
    {
        printf("%8s\t", utmpfp->ut_name);
        printf("%12s\t", utmpfp->ut_line);
        printf("%12s\t", utmpfp->ut_addr_v6[0]);
        printf("%12s\t", utmpfp->ut_addr_v6[1]);
        printf("%12s\t", utmpfp->ut_addr_v6[2]);
        printf("%12s\t", utmpfp->ut_addr_v6[3]);

#ifdef SHOWHOST
        printf("(%s)", utmpfp->ut_host);
#endif
        printf("\n");
    }
}

int main()
{
    struct utmp current_record;
    FILE *utmpfd = NULL;
    int reclen = sizeof(current_record); /* 打开登录信息记录文件 */
    if ((utmpfd = fopen(UTMP_FILE, "r")) == NULL)
    {
        printf("file open error!\n");
        return 0;
    }
    printf("file open success!\n");
    memset(&current_record, 0x00, reclen); /*循环读取*/
    while (fread(&current_record, sizeof(char), reclen, utmpfd) == reclen)
    { //read success
        show_info(&current_record);
        memset(&current_record, 0x00, reclen);
    }
    /* 关闭文件 */
    fclose(utmpfd);
    return 0;
}
