multiple producers, multiple consumers, linked list, one mutex

procedure ProduceData:
{
    while (true)
    {
        if (data != old_data)
        {
            ProduceNewData();
        }

        lock(mutex)
        ListInsert(new_data);
        unlock(mutex)

        check_return_status_of_insertion

    }

}

prodcedure ConsumeData:
{
    while (true)
    {

        lock(mutex)
        if (list != empty)
        {
            data = ListData();
            ListRemove(data);
        }
        unlock(mutex)

        do_something_with_data;

    }

}

1. starvation:
this solution is not cover starvation situation. if producer has the lock and consumer put to wait, and then context switch happens, consumerwoulden't get the chance to require the mutex for itself.
2. race condition:
mutex cover this problem entirly.
3. dead lock:
can't be, only one can hold the lock and only it can unlock it.


