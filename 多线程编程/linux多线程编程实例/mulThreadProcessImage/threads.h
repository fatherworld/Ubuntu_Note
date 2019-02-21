#ifndef THREADS_H
#define THREADS_H
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <string>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
static double array[10][10];
namespace ysThread{
    class thread_pro{
    public:
        pthread_t thread[2];
        pthread_mutex_t mut;


    public:
#if 0
        static double funtime(const string &str);
        static void *thread1(void *args);
        static void *thread2(void *args);
#endif
        void thread_create(void);

        void thread_wait(void);


        static void* thread1(void *args)
        {
            cout<< "thread1 : I'm thread 1" << endl;
            funtime("thread1 fun");
            cout<< "thread1 :main function is waiting me" << endl;
            pthread_exit(NULL);
        }


        static void *thread2(void *args)
        {
            cout<< "thread2 : I'm thread 2" << endl;
            funtime("thread2 fun");
            cout<< "thread2 :main function is waiting me" << endl;
            pthread_exit(NULL);
        }

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

    };
}

#endif // THREADS_H
