#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>

#define _PROGRAM_NAME_ "touchevery"
// mm-dd dhh:mi:ss programname [pid]:msg
#define _LOG_FORMAT_   "%02d-%02d %02d:%02d:%02d %s [%06d]:%s\n"
// $HOME/log/programname.yy.mm，如果￥HOME/log不存在，需要创建
#define _LOG_FILE_     "%s/log/%s.%04d%02d"

void catch_alarm(int num) {
	time_t nowtime = time(NULL);
	struct tm* nowtm = localtime(nowtime);
	
	char strLogFile[100];
	memset(strLogFile, 0x00, sizeof(strLogFile));
	sprintf(strLogFile, _LOG_FILE_, getenv("HOME"), _PROGRAM_NAME_, nowtm->tm_year+1900, nowtm->tm_mon+1);
	int fd = open(strLogFile, O_WRONLY|O_CREATE|O_APPEND, 0666);
	if (fd > 0) {
		perror("open file err");
		printf("file is %s\n", strLogFile);
		exit(1);
	}
	char buf[2048] = {0};
    sprintf(buf, _LOG_FORMAT_, nowtm->tm_mon+1, nowtm->tm_mday, nowtm->tm_hour, nowtm->tm_min, 
        nowtm->tm_sec, _PROGRAM_NAME_, getpid(), " This is yellow append info. ");
    write(fd, buf, strlen(buf));
    close(fd);
}

int main() {
    // 初始化需要的环境变量
    char *strHomeDir = getenv("HOME");
    printf("homedir is %s\n", strHomeDir);
    // 创建守护进程
    pid_t pid = fork();
    if (pid > 0) {
        exit(1);  // 父进程退出
    }
    setsid(); // 子进程当会长
    umask(0); // 设置掩码
    chdir(strHomeDir);
    close(0);
    // 设置信号捕捉，捕捉ALRM信号
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = catch_alarm;
    sigaction(SIGALRM, &act, NULL);

    // 设置时钟参数
    struct itimerval myit = {{60, 0}, {1, 0}}; // 每隔60秒来一次闹钟
    setitimer(ITIMER_REAL, &myit, NULL);
    // 循环等待
    while(1) {
        sleep(120);
    }
    return 0;
}



