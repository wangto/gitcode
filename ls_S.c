/*************************************************************************
	> File Name: ls_S.c
	> Author: WT
	> Mail: wangtong19951128@qq.com 
	> Created Time: Sat 25 Jul 2015 08:29:49 AM EDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>

#define MAX 256

void my_err(const char *err_string, int line)
{
    fprintf(stderr, "line:%d\n", line);
    perror(err_string);
    exit(0);
}

int main(int argc, char **argv)
{
    chdir(argv[1]);
    char filename[256][256], temp[256];
    int i, j, count = 0, how_big[256], how_temp;
    struct stat buf;
    struct dirent *ptr;
    DIR *dir;
    
    dir = opendir(argv[1]);
    while((ptr = readdir(dir)) != NULL){
        if(lstat(ptr->d_name, &buf) != -1){
            strcpy(filename[count], ptr->d_name);
            how_big[count] = buf.st_size;
        }else{
            my_err("lstat", __LINE__);
        }
        count++;
    }
    closedir(dir);
    

    for(i = 0;i < count - 1; i++)
    for(j = 0; j < count - 1 - i; j++){
        if(how_big[j] < how_big[j + 1]){
            how_temp = how_big[j];
            how_big[j] = how_big[j + 1];
            how_big[j + 1] = how_temp;
            strcpy(temp, filename[j]);
            strcpy(filename[j], filename[j + 1]);
            strcpy(filename[j + 1], temp);
        }
    }
    
    for(i = 0; i < count; i++)
        printf("%s\n", filename[i]);
    
    return 0;






}
