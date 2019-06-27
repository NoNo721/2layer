#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

using namespace std;

void procBar(int rate)
//进度条
{
	int ratep = rate/2;
	char bar[52];		//51个“=”，一个"\0"
	const char *label = "|/-\\";

	memset(bar, 0, 52*sizeof(char));
	
	int i = 0;
	while(i <= ratep)
	{
		bar[i] = '=';
		i++;
	}
	
	fflush(stdout);	
	printf("Proc:[%-51s][%d%%][%c]\r", bar, rate, label[rate%4]);	//"-"代表左对齐，‘\r’回车（即光标位于行首）
}

void myMkdir(const char *path)
//判断文件夹是否存在，不存在就创建
{
	 if(access(path,0)==-1)
        {
           printf("%s is set up.\n",path);
           mkdir(path,0777);
        }
}









