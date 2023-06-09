#include <fs.h>
#include <initrd.h>
#include <types.h>
#include <multibootinfo.h>
#include <screen.h>
#include <modules.h>

fs_node_t *fs_root = 0; // The root of the filesystem.
uint32_t read_fs(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer)
{
    // Has the node got a read callback?
    if (node->read != 0)
        return node->read(node, offset, size, buffer);
    else
        return 0;
}

uint32_t write_fs(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer)
{
    // Has the node got a write callback?
    if (node->write != 0)
        return node->write(node, offset, size, buffer);
    else
        return 0;
}

void open_fs(fs_node_t *node, uint8_t read, uint8_t write)
{
    // Has the node got an open callback?
    if (node->open != 0)
        return node->open(node);
}

void close_fs(fs_node_t *node)
{
    // Has the node got a close callback?
    if (node->close != 0)
        return node->close(node);
}

struct dirent *readdir_fs(fs_node_t *node, uint32_t index)
{
    // Is the node a directory, and does it have a callback?
    if ( (node->flags&0x7) == FS_DIRECTORY &&
         node->readdir != 0 )
        return node->readdir(node, index);
    else
        return 0;
}

fs_node_t *finddir_fs(fs_node_t *node, char *name)
{
    // Is the node a directory, and does it have a callback?
    if ( (node->flags&0x7) == FS_DIRECTORY &&
         node->finddir != 0 )
        return node->finddir(node, name);
    else
        return 0;
}
void filesystem_init() 
{
	module_t modules_fs_fs = MODULE("kernel.modules.fs.fs", "Filesystem for the initrd and kernel");
	char** deps;
	deps[0] = "kernel.modules.initrd.initrd";
	DEPS(modules_fs_fs, deps);
	uint32_t initrd_location = *((uint32_t*)mbi->mods_addr);
   	uint32_t initrd_end = *(uint32_t*)(mbi->mods_addr+4);
   	uint32_t placement_address = initrd_end;
	fs_root = initialise_initrd(initrd_location);
	INIT(modules_fs_fs);
}