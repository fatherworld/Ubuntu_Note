#include"threads.h"
using namespace ysThread;
int main()
{

    thread_pro mytpo;
    struct timeval tpstart,tpend;
    double timeuse;
    gettimeofday(&tpstart,NULL);

    pthread_mutex_init(&mytpo.mut,NULL);
    cout<<"main function is created thread" << endl;
    mytpo.thread_create();
    cout<<"main function is waiting thread" << endl;
    mytpo.thread_wait();

    gettimeofday(&tpend,NULL);
    timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse/=1000;
    cout << "MulThread " << " timeuse: " << timeuse << " ms" << endl;

    cout << "signle thread time using: " <<
    mytpo.funtime("main fun") + mytpo.funtime("main fun") << " ms" << endl;

    return 0;
}
