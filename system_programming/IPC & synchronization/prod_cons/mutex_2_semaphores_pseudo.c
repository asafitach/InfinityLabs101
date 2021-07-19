multiple producers, multiple consumers, queue, one mutex, 2 semaphores

procedure ProduceData:
{
    while (true)
    {
        if (data != old_data)
        {
            ProduceNewData();
        }
        sem_wait(free_space);
        lock(mutex)
        EnQueue(new_data);
        unlock(mutex)
        sem_post(occupied_space);
        check_return_status_of_insertion

    }

}

prodcedure ConsumeData:
{
    while (true)
    {
        sem_wait(occupied_space)
        lock(mutex)
        data = DeQueue
        unlock(mutex)
        sem_post(free_space);

        do_something_with_data;

    }

}

1. starvation:
cover starvation. if producer has the lock and consumer put to wait, and then context switch happens, consumer woulden get the control next time because semaphore works with queue unlike mutex.
2. race condition:
mutex cover this problem entirly.
3. dead lock:
can't be, the order of semaphore is detrmined each one require one and release one. 


