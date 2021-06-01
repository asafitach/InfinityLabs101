#include <unistd.h>  /* getpid */
#include <pthread.h>  /* create join */
#include <stdatomic.h>   /* __sync_fetch_and_add */

#include "uid.h"

/*********************UID API definition***************************/

/*********************UidCreate***************************/

ilrd_uid_t UidCreate(void) /*This has a static counter*/
{
	static size_t counter = 0;
	
	ilrd_uid_t uid = {0, 0, 0};
	
	uid.timestamp = time(NULL);
	__sync_fetch_and_add(&counter, 1);
	uid.counter = counter;
	uid.pid = getpid();

	return (uid);
}

/*********************GetBadUid***************************/

ilrd_uid_t GetBadUid(void)
{
	ilrd_uid_t uid = {0, 0, 0};

	return (uid);
}

/*********************UidIsSame***************************/
	
int UidIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	return ((uid1.timestamp == uid2.timestamp && uid1.counter == uid2.counter && uid1.pid == uid2.pid ));
}

/*********************END***************************/

