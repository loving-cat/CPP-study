#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<unistd.h>
#include <fcntl.h>
#include<string.h>

// //设计一个以位图去传参
// #define ONE 1       // 1 0000 0001
// #define TWO (1<<1)  // 2 0000 0010
// #define THREE (1<<2)// 3 0000 0100
// #define FOUR (1<<3) // 4 0000 1000

// void print(int flag)
// {
//     if(flag&ONE)
//         printf("one\n");
//     if(flag&TWO)
//         printf("two\n");
//     if(flag&THREE)
//         printf("three\n");
//     if(flag&FOUR)
//         printf("four\n");
// }

// int main()
// {
//     print(ONE);
//     printf("\n");
//     print(TWO);
//     printf("\n");
//     print(ONE|TWO);
//     printf("\n");
//     print(ONE|TWO|THREE);
//     printf("\n");
//     print(ONE|FOUR);
//     printf("\n");
//     print(ONE|TWO|THREE|FOUR);
//     printf("\n");


//     return 0;
// }
int main()
{
    FILE *fp = fopen("log.txt","w");
    if(fp==NULL)return 1;
    printf("fd:%d\n",fp->_file);
    fwrite("hello",5,1,fp);
    fclose(fp);



    // const char *message = "hello Linux file!";
    // //1是标准输出，直接写在显示器
    // write(1,message,strlen(message));

    // fprintf(stdout,"hello: %d\n",10);
    // fflush(stdout);

    // int fda = open("loga.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    // printf("fda: %d\n",fda);

    // int fdb = open("logb.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    // printf("fdb: %d\n",fdb);

    // int fdc = open("logc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    // printf("fdc: %d\n",fdc);

    // int fdd = open("logd.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    // printf("fdd: %d\n",fdd);

    //把系统默认的umask 设置为0
    //umask(0);
    // system call
                            //只写|不存在就创建|如果文件存在再次打开则清空文件内容（截断）
    //int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    // int fd = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);

    // if (fd < 0)
    // {
    //     perror("open");
    //     return 1;
    // }
    // const char *message = "hello Linux file!\n";
    // write(fd,message,strlen(message));
    // close(fd);
    return 0;
}