#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#define FILE_TEST ("filetest")
int main(int argc, char** argv)
{
    #define FILE_NAME (argv[1])
    if(argc != 2)
    {
        printf("argc should be 2: temp file_name\n");
        return -1;
    }
    
    // get file size
    struct stat statData;
    int ret = stat(FILE_NAME, &statData);
    if(ret != 0)
    {
        printf("get %s stat failed\n", FILE_NAME);
        return -1;
    }
    int filesize = statData.st_size;
    
    // read file data
    char* pSrcData = malloc(filesize);
    char* pDstData = malloc(filesize);
    int srcfd = open(FILE_TEST, O_RDONLY);
    if(srcfd == -1)
    {
        printf("open file %s failed\n", FILE_TEST);
        return -1;
    }
    int dstfd = open(FILE_NAME, O_RDONLY);
    if( dstfd == -1)
    {
        printf("open file %s failed\n", FILE_NAME);
        return -1;
    }
    read(srcfd, pSrcData, filesize);
    read(dstfd, pDstData, filesize);
    close(srcfd);
    close(dstfd);
    int i = 0;
    for(i = 0; i < filesize; i++)
    {
        if(pSrcData[i] != pDstData[i])
        {
            break;
        }
    }
    if(i < filesize)
    {
        printf("file(%s) and file(%s) not same\n",FILE_NAME, FILE_TEST);
        return -1;
    }
    else
    {
        printf("file(%s) and file(%s) same\n", FILE_NAME, FILE_TEST);
        return 0;
    }
}