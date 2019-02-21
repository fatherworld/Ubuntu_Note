#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <string>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;

static pthread_t thread[2];
static pthread_mutex_t mut;
static double array[10][10];

static double funtime(const string &str)
{
    struct timeval tpstart,tpend;
    double timeuse;
    gettimeofday(&tpstart,NULL);

    int loop = 1000000;
    while(loop--)
    {
        for (int i = 0; i < 10; ++i)
        {
            for(int j = 0; j < 10;++j)
            {
                array[i][j] = 0.63;
                array[i][j] /= 0.96;
            }
        }
    }
    gettimeofday(&tpend,NULL);
    timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse/=1000;
    cout << str << " timeuse: " << timeuse << " ms" << endl;
    return timeuse;
}


void *thread1(void *args)
{
    cout<< "thread1 : I'm thread 1" << endl;
    funtime("thread1 fun");
    cout<< "thread1 :main function is waiting me" << endl;
    pthread_exit(NULL);
}

void *thread2(void *args)
{
    cout<< "thread2 : I'm thread 2" << endl;
    funtime("thread2 fun");
    cout<< "thread2 :main function is waiting me" << endl;
    pthread_exit(NULL);
}

void thread_create(void)
{
    int temp;
    memset(&thread, 0, sizeof(thread));
    if((temp = pthread_create(&thread[0], NULL, thread1, NULL)) != 0)
        cout<<"thread1 is created failed" << endl;
    else
        cout<<"thread1 is created " << endl;
    if((temp = pthread_create(&thread[1], NULL, thread2, NULL)) != 0)
        cout<<"thread2 created failed" << endl;
    else
        cout<<"thread2 is created" << endl;
}

void thread_wait(void)
{
    if(thread[0] !=0)
    {
        pthread_join(thread[0],NULL);
        cout<<("thread1 is end \n");
    }
    if(thread[1] !=0)
    {
        pthread_join(thread[1],NULL);
        cout<<("thread2 is end \n");
    }
}


int main1()
{
    struct timeval tpstart,tpend;
    double timeuse;
    gettimeofday(&tpstart,NULL);

    pthread_mutex_init(&mut,NULL);
    cout<<"main function is created thread" << endl;
    thread_create();
    cout<<"main function is waiting thread" << endl;
    thread_wait();

    gettimeofday(&tpend,NULL);
    timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse/=1000;
    cout << "MulThread " << " timeuse: " << timeuse << " ms" << endl;

    cout << "signle thread time using: " <<
    funtime("main fun") + funtime("main fun") << " ms" << endl;

    return 0;
}
