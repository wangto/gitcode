/*************************************************************************
	> File Name: test_lls.c
	> Author: WT
	> Mail: wangtong19951128@qq.com 
	> Created Time: Tue 21 Jul 2015 01:18:22 AM EDT
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<dirent.h>
#define MAX 256

void my_err(char *err_string, int line)
{
    fprintf(stderr, "line:%d", line);
    perror(err_string);
    exit(0);
}

void display(char *path)
{
    chdir(path);
    DIR *dir;
    struct stat buf;
    struct dirent *ptr;
    char string[MAX], filename[MAX];
    memset(string, 0, MAX);
    memset(filename, 0, MAX);
    strcpy(filename, path);
    int i = 0, count = 0;
    dir = opendir(path);
    while((ptr = readdir(dir)) !=  NULL){
        printf("%s \n", ptr->d_name);
        if(lstat(ptr->d_name, &buf) == -1)
            my_err("lstat", __LINE__);
        if(S_ISDIR(buf.st_mode)){
            if(filename[strlen(path) - 1] != '/')
                filename[strlen(path)] = '/';
            if(strcmp(ptr->d_name, ".") == 0)
                continue;
            if(strcmp(ptr->d_name, "..") == 0)
                continue;
            filename[strlen(filename)] = '\0';
            strcat(filename, ptr->d_name);
            printf("%s\n", filename);
            display(filename);       
            chdir(path);
            memset(filename, 0, MAX);
            strcpy(filename, path);
        } 
    }
    closedir(dir);
    return;
}


int main(int argc, char **argv)
{
    display(argv[1]);
}

