#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include<string.h>
#include <string>
#include <stdio.h>
#include<stdlib.h>
using namespace std;

//thread function pamter
struct theradPamter{
    int threadindex;
    string str;
};

pthread_t thread[2];
pthread_mutex_t mut;

double array1[10][10];
double array2[10][10];
double array0[10][10];


double funtime(const string &str, const int index)
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
                if (index == 1)
                {
                    array1[i][j] = 1;
                    array1[i][j] /= 2;
                }else if(index == 2)
                {
                    array2[i][j] = 2;
                    array2[i][j] /= 2;
                }else
                {
                    array0[i][j] = 3;
                    array0[i][j] /= 2;
                }
            }
        }
    }

    gettimeofday(&tpend,NULL);
    timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse/=1000;
    cout << str << " timeuse: " << timeuse << " ms" << endl;
    return timeuse;
}


static void *thread1(void *args)
{
    cout<< "thread1 : I'm thread 1" << endl;
    theradPamter *tp = (theradPamter *) args;
    funtime(tp->str, tp->threadindex);
    cout<< "thread1 :main function is waiting me" << endl;
    pthread_exit(NULL);
}

static void *thread2(void *args)
{
    cout<< "thread2 : I'm thread 2" << endl;
    theradPamter *tp = (theradPamter *) args;
    funtime(tp->str, tp->threadindex);
    cout<< "thread2 :main function is waiting me" << endl;
    pthread_exit(NULL);
}

static void thread_create(theradPamter *tp1, theradPamter *tp2)
{
    int temp;
    memset(&thread, 0, sizeof(thread));

    if((temp = pthread_create(&thread[0], NULL, thread1, (void *)tp1)) != 0)
        cout<<"thread1 is created failed" << endl;
    else
        cout<<"thread1 is created " << endl;
    if((temp = pthread_create(&thread[1], NULL, thread2, (void *)tp2)) != 0)
        cout<<"thread2 created failed" << endl;
    else
        cout<<"thread2 is created" << endl;

}

static void thread_wait(void)
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


void printresult()
{
    cout << "array1" << endl;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            cout << " " << array1[i][j];
        }
        cout << endl;
    }

    cout <<"array2" <<endl;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            cout << " " << array2[i][j];
        }
        cout << endl;
    }

    cout <<"array0" <<endl;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            cout << " " << array0[i][j];
        }
        cout << endl;
    }

}


int main2()
{
    struct timeval tpstart,tpend;
    double timeuse;
    gettimeofday(&tpstart,NULL);

    pthread_mutex_init(&mut,NULL);
    cout<<"main function is created thread" << endl;

    theradPamter *tp1 = new theradPamter;
    theradPamter *tp2 = new theradPamter;
    tp1->threadindex = 1;
    tp1->str = "thread1 fun";
    tp2->threadindex = 2;
    tp2->str = "thread2 fun";

    thread_create(tp1, tp2);

    cout<<"main function is waiting thread" << endl;
    thread_wait();

    delete tp1;
    tp1 = NULL;
    delete tp2;
    tp2 = NULL;

    gettimeofday(&tpend,NULL);
    timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse/=1000;
    cout << "MulThread " << " timeuse: " << timeuse << " ms" << endl;

    cout << "signle thread time using: " <<
    funtime("main fun",0) + funtime("main fun",0) << " ms" << endl;

    printresult();

    return 0;
}
