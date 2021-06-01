#include <stddef.h>  /* size_t */
#include <time.h>
#include <unistd.h>
#include "uid.h"

ilrd_uid_t UidCreate(void)
{
    static size_t counter = 0;
    ilrd_uid_t new_uid = {0}; 
    
    new_uid.timestamp = time(NULL);
    __sync_fetch_and_add(&counter, 1);
    new_uid.counter = counter;
    new_uid.pid = getpid();
    
    return(new_uid);    
}

ilrd_uid_t GetBadUid(void)
{
    ilrd_uid_t new_uid = { 0, 0, 0 };
    return(new_uid); 
}



int UidIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	return (uid1.counter == uid2.counter && uid1.pid == uid2.pid);
}



