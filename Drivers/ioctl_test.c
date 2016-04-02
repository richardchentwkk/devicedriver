#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/ioctl.h>
#include "opcode.h"
int main(int argc, char *argv[])
{
    int fd;
    int num = 0;
    int input;
    char cmd[30];
    if (argc > 1) num = atoi(argv[1]);
    if (num < 0) num = 0xff;

    fd = open("/dev/char_device", O_RDONLY);
    if (fd == -1) {
        printf("Can't open /dev/char_device\n");
        return -1;
    }
    do{
    printf("IO Control Test\n");
    printf("Please input command!\n");
    printf("1)IOCTL_WRITE 2)EXIT\n");
    scanf("%s",cmd);
    if (!strcmp(cmd,"IOCTL_WRITE"))
    {
        ioctl(fd, IOCTL_WRITE , num);
        printf("Debug correct\n");
    }else
    {
        printf("Fail to add command\n");
    };
    printf("Done. Wait 1 seconds...\n");
    sleep(1);
    }
    while(strcmp(cmd,"EXIT"));
    close(fd);

    return 0;
}

