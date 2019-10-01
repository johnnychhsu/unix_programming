#include <unistd.h>

int myDup2(int, int);

int main()
{
    myDup2(1, 5);
    while(1)
    {
        sleep(1);
    }
    return 0;
}

int myDup2(int fd1, int fd2)
{
    /*****
    First check whether fd1 equals fd2. Then we keep duplicating fd1 until the new fd equals fd2.
    Note that we should keep those open fd in an array, so that we can close them all after we reach fd2.
    *****/
    if (fd1 == fd2) return fd2;
    int fd, newfd;
    fd = close(fd2);
    
    int length = 0;
    int fds[fd2];
    for(;;)
    {
        newfd = dup(fd1);
        fds[length] = newfd;
        if(newfd == fd2) break;
        length++;
    }

    for(int i=0; i<length; i++)
    {
        close(fds[i]);
    }

    return newfd;
}
