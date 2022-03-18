#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
#include "pthread.h"

#if __APPLE__
    #define MPV "/opt/homebrew/bin/mpv"
#elif __linux__
    #define MPV "/bin/mpv"
#endif

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct video 
{
    char path[256];
    int stream_time;
    int begin_time;
    int end_time;
};

void loadplaylist(struct video* vds, char *config_path)
{
    FILE *fp;
    int cnt=0;
    int stream_time,begin_time,end_time;
    char path[256];

    fp = fopen(config_path,"r");
    while(fscanf(fp,"%s %d %d %d", path,&stream_time,&begin_time,&end_time) != EOF)
    {
    	strcpy(vds[cnt].path,path);
    	vds[cnt].stream_time = stream_time;
    	vds[cnt].begin_time = begin_time;
    	vds[cnt].end_time = end_time;
    	cnt++;
    }

}

void loopstream(struct video *vd)
{
    int allocated_time,nloop;
    char option[128];
    
    //ループ回数を計算
    allocated_time = vd->end_time - vd->begin_time;
    nloop = allocated_time / vd->stream_time - 1;
    sprintf(option,"--loop-file=%d",nloop);
    //スタートのタイミングを探る
    for(;;)
    {
    	if(time(NULL) >= vd->begin_time)
    	{
    	    execl(MPV,MPV,option,"--keep-open","--fs"  ,vd->path,NULL);	
    	    break;
    	}
    }
}


void stream_process(struct video *vd)
{
    pid_t pid;
    pid = fork();
    if(pid < 0)
    {
	   printf("create proc fail\n");
    }
    else if(pid == 0)
    {
	   loopstream(vd);
    }
    else
    {
    	for(;;)
    	{
    	    if((int)time(NULL) > vd->end_time)
    	    {
        		kill(pid,SIGINT);
        		wait(NULL);
        		break;
    	    }
    	}
    }
}

int main (int argc, char *argv[])
{
    FILE *fp;
    pthread_t th[2];
    int now = (int)time(NULL);
    printf("now is %d\n",now);
    struct video vd[2];
    //struct video vd1 = {"./movie/sample-5s.mp4",5,now+1,now+11};
    //struct video vd2 = {"./movie/sample-10s.mp4",10,now+6,now+26};
    //vd[0]=vd1;
    //vd[1]=vd2;
    int ret;

    loadplaylist(vd,"./schedule.txt");
    for(int i=0;i<2;i++)
    {
	   pthread_create(&th[i],NULL,(void*)stream_process,&vd[i]);
    }
    //終了
    for(int i=0;i<2;i++)
    {
	   ret = pthread_join(th[i],NULL);
    }
    return 0;
}
