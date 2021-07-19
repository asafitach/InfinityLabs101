#include <ext2fs/ext2_fs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <string.h>

#define DEVICE "/dev/ram0"


#define SUPER_BLOCK struct ex2_super_block
#define SUPER_BLOCK_OFFSETT 1024
#define SUPER_BLOCK_SIZE sizof(struct ext2_super_block)

typedef struct ext2_super_block super_block_t;
typedef struct ext2_group_desc group_t;


void PrintSuperBlock(super_block_t super);
super_block_t GetSuperBlock(const char *device_path);
void PrintGroupDescriptor(group_t group);
group_t GetFirstGroupDecriptor(const char *device);

int main()
{
    super_block_t super = {0};
    super_block_t error_check = {0};
    group_t group = {0};
    group_t g_error_check = {0};

    super = GetSuperBlock(DEVICE);
    if (0 == memcmp(&super, &error_check, sizeof(super_block_t)))
    {
        return (1);
    }

    PrintSuperBlock(super);

    group = GetFirstGroupDecriptor(DEVICE);
    if (0 == memcmp(&group, &g_error_check, sizeof(super_block_t)))
    {
        return (1);
    }

    PrintGroupDescriptor(group);


    return (0);
}


super_block_t GetSuperBlock(const char *device_path)
{
    super_block_t super = {0};
    const int error = 0;
    int fd = 0;
    fd = open(DEVICE, O_RDONLY);
    if (0 > fd)
    {
        perror("device not opened");
        return (super);/* super is 0 */
    }

	lseek(fd, SUPER_BLOCK_OFFSETT, SEEK_SET); 
	read(fd, &super, sizeof(super));


    if (super.s_magic != EXT2_SUPER_MAGIC) 
    {
        perror("Not a Ext2 filesystem\n");
		return(*(super_block_t*)&error);
	}
    return (super);
} 


void PrintSuperBlock(super_block_t super)
{
	printf("Reading super-block from device " DEVICE ":\n"
	       "Inodes count            : %u\n"
	       "Blocks count            : %u\n"
	       "Reserved blocks count   : %u\n"
	       "Free blocks count       : %u\n"
	       "Free inodes count       : %u\n"
	       "First data block        : %u\n"
	       "Block size              : %u\n"
	       "Blocks per group        : %u\n"
	       "Inodes per group        : %u\n"
	       "Creator OS              : %u\n"
	       "First non-reserved inode: %u\n"
	       "Size of inode structure : %hu\n"
	       ,
	       super.s_inodes_count,  
	       super.s_blocks_count,
	       super.s_r_blocks_count,     /* reserved blocks count */
	       super.s_free_blocks_count,
	       super.s_free_inodes_count,
	       super.s_first_data_block,
	       1024 << super.s_log_block_size,
	       super.s_blocks_per_group,
	       super.s_inodes_per_group,
	       super.s_creator_os,
	       super.s_first_ino,          /* first non-reserved inode */
	       super.s_inode_size);
}

group_t GetFirstGroupDecriptor(const char *device)
{
	super_block_t super = {0};
	group_t group = {0};
	int fd = 0;
    unsigned int block_size = 0;
    unsigned long bit_counter = 0;
    char *runner = NULL;

	/* open floppy device */

	if ((fd = open(DEVICE, O_RDONLY)) < 0) 
    {
		perror(DEVICE);
		return(group);  /* error while opening the floppy device */
	}

	/* read super-block */

	lseek(fd, SUPER_BLOCK_OFFSETT, SEEK_SET); 
	read(fd, &super, sizeof(super));

	if (super.s_magic != EXT2_SUPER_MAGIC) 
    {
        perror("Not a Ext2 filesystem\n");
		return(group);
	}
		
	block_size = 1024 << super.s_log_block_size;

	/* read group descriptor */
    for (int i = 0; i < 1000; ++i)
    {
	lseek(fd, sizeof(super_block_t), SEEK_CUR);
	/*lseek(fd, SUPER_BLOCK_OFFSETT + super.s_log_block_size, SEEK_SET);*/
	read(fd, &group, sizeof(group));
    runner = (char *)&group;
    for (int j = 0; j < sizeof(group_t); ++j)
    {
        if (0 != *runner)
        {
            printf("not zero at %lu byte\n", bit_counter);
        }
        ++bit_counter;
        ++runner;
    }
    }
	close(fd);

    return (group);
}

void PrintGroupDescriptor(group_t group)
{
    	printf("Reading first group-descriptor from device " DEVICE ":\n"
	       "Blocks bitmap block: %u\n"
	       "Inodes bitmap block: %u\n"
	       "Inodes table block : %u\n"
	       "Free blocks count  : %u\n"
	       "Free inodes count  : %u\n"
	       "Directories count  : %u\n"
	       ,
	       group.bg_block_bitmap,
	       group.bg_inode_bitmap,
	       group.bg_inode_table,
	       group.bg_free_blocks_count,
	       group.bg_free_inodes_count,
	       group.bg_used_dirs_count);    /* directories count */
}