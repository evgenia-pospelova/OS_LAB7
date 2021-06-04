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


void signal_handler(int signal)
{

 cout << "Именованный канал закрыт!" << endl;

}

void* func(void* )
{
    int buff;
    while(flag){
        buff = 0;
        read(pipefd,&buff,4);
        if (buff != 0){
            cout << buff << endl;
            cout.flush();
        }
    }
    return NULL;
}

int main()
{
  pthread_t thread1;
  mkfifo("/tmp/file1", 0644);
  pthread_create(&thread1, NULL, func, NULL);
  getchar();
  flag=false;
  pthread_join(thread1, NULL);
  close(pipefd);
  unlink("/tmp/file1");
  return 0;


}
