#ifndef __UID_H__
#define __UID_H__

#include <stddef.h>      /* size_t */
#include <time.h>        /* time_t */
#include <sys/types.h>   /* pid_t */



typedef struct 
{
	time_t timestamp;
	size_t counter; /*incement for every create*/
	pid_t pid;	

} ilrd_uid_t;


/*Description: The functions creates a valid UID
@return: uid_t
@errors: 
*/

ilrd_uid_t UidCreate(void); /*This has a static counter*/


/*Description: The functions creates a non-valid UID
@return: uid_t
@errors: 
*/

ilrd_uid_t GetBadUid(void);

/*Description: the function checks if two UIDs are the same.
@return: BOOL
@errors: 
*/

int UidIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2);


#endif /* __UID_H__ */
