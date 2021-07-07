#include <ext2fs/ext2fs.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BASE_OFFSET 1024              
#define BLOCK_OFFSET(block) (BASE_OFFSET + (block-1)*g_s_block_size)

static unsigned int g_s_block_size = 0;

struct ext2_super_block GetSuperBlock(char *device);
struct ext2_group_desc GetFirstGroupDecriptor(char *device);
struct ext2_inode GetDirectoryINode(char *device, int bg_inode_table);
int GetFileINode(char *device, char *target_file, struct ext2_inode inode);
struct ext2_inode PrintFileFromInode(char *device, int inode_num, int bg_inode_table);


int main()
{
    struct ext2_super_block super_block = GetSuperBlock("/dev/ram0");

    struct ext2_group_desc group_desc = GetFirstGroupDecriptor("/dev/ram0");  

    struct ext2_inode inode = GetDirectoryINode("/dev/ram0", group_desc.bg_inode_table);

    int inode_num = GetFileINode("/dev/ram0", "t.c", inode);

    PrintFileFromInode("/dev/ram0", inode_num, group_desc.bg_inode_table);

    return (0);
}



struct ext2_super_block GetSuperBlock(char *device)
{
    struct ext2_super_block super;
    int fd = open(device, O_RDONLY);
    if (fd < 0)
    {
        perror("open failed");
    }

    lseek(fd, 1024, SEEK_SET);
    read(fd, &super, sizeof(super));
    close(fd);

    g_s_block_size = 1024 << super.s_log_block_size;

    printf("\n\nReading super-block from device %s:\n"
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
        device,
        super.s_inodes_count,  
        super.s_blocks_count,
        super.s_r_blocks_count,     /* reserved blocks count */
        super.s_free_blocks_count,
        super.s_free_inodes_count,
        super.s_first_data_block,
        g_s_block_size,
        super.s_blocks_per_group,
        super.s_inodes_per_group,
        super.s_creator_os,
        super.s_first_ino,          /* first non-reserved inode */
        super.s_inode_size);


    return(super);
}

struct ext2_group_desc GetFirstGroupDecriptor(char *device)
{
    struct ext2_group_desc group;

    int fd = open(device, O_RDONLY);
    if (fd < 0)
    {
        perror("open failed");
    }

    lseek(fd, g_s_block_size, SEEK_SET);
    read(fd, &group, sizeof(group));

    printf("\n\nReading first group-descriptor from device %s :\n"
	       "Blocks bitmap block: %u\n"
	       "Inodes bitmap block: %u\n"
	       "Inodes table block : %u\n"
	       "Free blocks count  : %u\n"
	       "Free inodes count  : %u\n"
	       "Directories count  : %u\n"
	       ,
           device,
	       group.bg_block_bitmap,
	       group.bg_inode_bitmap,
	       group.bg_inode_table,
	       group.bg_free_blocks_count,
	       group.bg_free_inodes_count,
	       group.bg_used_dirs_count);    /* directories count */

    
   close(fd);

    return(group);
}


struct ext2_inode GetDirectoryINode(char *device, int bg_inode_table)
{	
    int fd = open(device, O_RDONLY);
    if (fd < 0)
    {
        perror("open failed");
    }


	struct ext2_inode inode; 
    lseek(fd, bg_inode_table * g_s_block_size + sizeof(struct ext2_inode), SEEK_SET);
    read(fd, &inode, sizeof(struct ext2_inode));
    struct ext2_dir_entry_2 dir;
    lseek(fd,g_s_block_size * inode.i_block[0],SEEK_SET);
    read(fd,&dir,sizeof(struct ext2_dir_entry_2));

    int size = 0;

    while (size < inode.i_size) 
    {
            char file_name[EXT2_NAME_LEN+1];
            memcpy(file_name, dir.name, dir.name_len);
            file_name[dir.name_len] = '\0';          
            printf("inode : %u <--> file name: %s file type: %d\n", dir.inode, file_name, dir.file_type);
            size += dir.rec_len;
            dir = *(struct ext2_dir_entry_2 *)((char*)&dir + dir.rec_len);    
    }

    close(fd);

    return (inode);
}

int GetFileINode(char *device, char *target_file, struct ext2_inode inode)
{
    int fd = open(device, O_RDONLY);
    if (fd < 0)
    {
        perror("open failed");
    }

    struct ext2_dir_entry_2 dir;
    lseek(fd,g_s_block_size * inode.i_block[0],SEEK_SET);
    read(fd,&dir,sizeof(struct ext2_dir_entry_2));

    int size = 0;

    while (size < inode.i_size) 
    {
            char file_name[EXT2_NAME_LEN+1];
            memcpy(file_name, dir.name, dir.name_len);
            file_name[dir.name_len] = '\0';           
            printf("inode : %u <--> file name: %s \n", dir.inode, file_name);
            if (strcmp(target_file, file_name) == 0)
            {
                close(fd);
                return (dir.inode);
            }
            size += dir.rec_len;
            dir = *(struct ext2_dir_entry_2 *)((char*)&dir + dir.rec_len);  
    }

    close(fd);

    return (-1);
}

struct ext2_inode PrintFileFromInode(char *device, int inode_num, int bg_inode_table)
{
    int fd = open(device, O_RDONLY);
    if (fd < 0)
    {
        perror("open failed");
    }


	struct ext2_inode inode; 
    lseek(fd, bg_inode_table * g_s_block_size + ((inode_num - 1) * sizeof(struct ext2_inode)), SEEK_SET);
    read(fd, &inode, sizeof(struct ext2_inode));  
    

    char buffer[inode.i_size];

    lseek(fd,g_s_block_size * inode.i_block[0],SEEK_SET);
    read(fd, buffer, inode.i_size); 

    buffer[inode.i_size] = '\0';
    printf("\nPrint File: \n\n");
    printf("%s \n", buffer);

    return (inode);      
}



