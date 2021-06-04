#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>


using namespace std;

bool flag = true;
int pipefd;
pthread_t thread;


void signal_handler(int signal)
{

 cout << "Именованный канал закрыт!" << endl;

}

void* func(void* )
{
    int buff;
    while(flag){
        write(pipefd, &buff, sizeof(int));
        signal(13,signal_handler);
        sleep(1);
    }
    return NULL;

}

void* openThread(void* flag){
    while(flag){
        int error = open("/tmp/file1", O_WRONLY|O_NONBLOCK);
        if (error == -1){
            cout << "Невозможно открыть канал!" << endl;
            sleep(1);
        } else {
            pthread_create(&thread, NULL, func, NULL);
            return NULL;
        }
    }
}

int main()
{
  pthread_t thread1;
  mkfifo("/tmp/file1", 0644);
  pthread_create(&thread1, NULL, openThread, NULL);
  getchar();
  flag=false;
  pthread_join(thread1, NULL);
  pthread_join(thread,NULL);
  close(pipefd);
  unlink("/tmp/file1");
  return 0;


}
