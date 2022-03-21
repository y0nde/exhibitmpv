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

int today_epoch()
{
    time_t now = time(NULL);
    struct tm *x = localtime(&now);
    x->tm_sec = 0;
    x->tm_min = 0;
    x->tm_hour = 0;
    time_t today = mktime(x);
    return (int)today;
}

void loadplaylist(struct video* vds, char *config_path)
{
    FILE *fp;
    int cnt=0;
    int stream_time,begin_time,end_time;
    char path[256];

    //today
    int today = today_epoch();
    printf("now is %d\n",(int)time(NULL));
    printf("today is %d\n",today);

    //read
    fp = fopen(config_path,"r");

    while(fscanf(fp,"%s %d %d %d", path,&stream_time,&begin_time,&end_time) != EOF)
    {
        //printf("%d <=> %s %d %d %d\n",cnt,path,stream_time,begin_time,end_time);
    	strcpy((vds+cnt)->path,path);
    	(vds+cnt)->stream_time = stream_time;
    	(vds+cnt)->begin_time = today + begin_time;
    	(vds+cnt)->end_time = today + end_time;
        //printf("%d begin_time <=> %d\n",cnt,(vds+cnt)->begin_time);
        //printf("%d end_time   <=> %d\n",cnt,(vds+cnt)->end_time);
    	cnt++;
    }

}

void singlestream(struct video *vd)
{
    int wait_time;
    //スタートのタイミングを探る
    if(vd->begin_time > (int)time(NULL))
    {
        wait_time = vd->begin_time - (int)time(NULL) - 1;
        if(wait_time > 0)
        {
           sleep(wait_time); 
        }
    }
    
    for(;;)
    {
        if(time(NULL) >= vd->begin_time)
        {
            execl(MPV,MPV,"--keep-open","--fs",vd->path,NULL); 
            //execl("/usr/local/bin/iina","/usr/local/bin/iina","--mpv-keep-open","--mpv-fs",vd->path,NULL); 
            break;
        }
        else if(time(NULL) > vd->begin_time)
        {
            break;
        }
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

void single_stream_process(struct video *vd)
{
    pid_t pid;
    pid = fork();
    if(pid < 0)
    {
       printf("create proc fail\n");
    }
    else if(pid == 0)
    {
       singlestream(vd);
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

void loop_stream_process(struct video *vd)
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
    int now = (int)time(NULL);
    int nchapter;
    int prev_begin = 0;
    if(argc < 3)
    {
        printf("exhibitstream [shedule.txt] [num_chapter]\n");
        exit(0);
    }
    else
    {
        nchapter = atoi(argv[2]);
    }

    //スレッドとvideo配列を初期化
    pthread_t th[nchapter];
    struct video vd[nchapter];

    //struct video vd[2];
    //struct video vd1 = {"./movie/sample-5s.mp4",5,now+1,now+11};
    //struct video vd2 = {"./movie/sample-10s.mp4",10,now+6,now+26};
    //vd[0]=vd1;
    //vd[1]=vd2;
    int ret;

    loadplaylist(vd,argv[1]);

    for(int i=0;i<nchapter;i++)
    {
        if(i!=0)
        {
            int wait_time;
            //スタートのタイミングを探る
            if(prev_begin > (int)time(NULL))
            {
                wait_time = prev_begin - (int)time(NULL);
                if(wait_time > 0)
                {
                   sleep(wait_time); 
                }
            }
        }
        pthread_create(&th[i],NULL,(void*)single_stream_process,&vd[i]);
        prev_begin = vd[i].begin_time;
    }
    //終了
    for(int i=0;i<nchapter;i++)
    {
	   ret = pthread_join(th[i],NULL);
    }
    return 0;
}
