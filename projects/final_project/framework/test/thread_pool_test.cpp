#include <iostream>
#include <queue>
#include <thread>
#include "thread_pool.hpp"
//#include "waitable_queue.hpp"
//#include "priority_queue.hpp"


using namespace ilrd;
using std::cout;
using std::endl;

class MyTask : public ThreadPool::ITask
{
   void Run()
   {
        static int i = 0;
        cout << "MyTask  " << ++i << endl;
   }
};

class Functor 
{
public:
    int operator()(void)
    {
        cout << "in Functor" << endl;
        sleep(4);
        return (1);
    }
};

void MyTask2();

int main()
{
    size_t numOfThreads = 10;
    unsigned int niceness = 0;
    ThreadPool tp(numOfThreads, niceness);

    std::shared_ptr<MyTask> ptr(new MyTask);
    tp.AddTask(ptr);

    std::function<void(void)> funcPtr = &MyTask2;  // std::function - wrapper to fnction or functor
    std::shared_ptr<ThreadPool::ITask> ptr2(new ThreadPool::FunctionTask(funcPtr));
    tp.AddTask(ptr2);

    std::shared_ptr<ThreadPool::ITask> ptr3 = std::make_shared<ThreadPool::FunctionTask>(MyTask2);
    tp.AddTask(ptr3);
    tp.AddTask(ptr3);


    std::shared_ptr<ThreadPool::FunctorTask<int>> task_ptr = std::make_shared<ThreadPool::FunctorTask<int>>(Functor());
    tp.AddTask(task_ptr);
    cout << task_ptr->Get() << endl;

/*     for(size_t i = 0; i < 100; i++)
    {
        std::shared_ptr<MyTask> ptr(new MyTask);
        tp.AddTask(ptr, ThreadPool::priority_t::MED);

        if(i == 30)
        {
            tp.SetNumOfThreads(3);
        }
v

        if(i == 50)
        {
            tp.Pause();
            sleep(3);
            tp.Resume();
        }

        
    } */

    sleep(2);
}


void MyTask2()
{
    static int i = 0;
    cout << "MyTask2  " << ++i << endl;
}


