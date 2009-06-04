#ifndef _VFS_INIT_H_
#define _VFS_INIT_H_

#include "vfs_types.h"
#include "vfs_profile.h"

bool InitWriteProfile(vfs::CVirtualProfile &rProf, vfs::Path const& profileRoot);
bool InitVirtualFileSystem(vfs::Path const& vfs_ini);
bool InitVirtualFileSystem(std::list<vfs::Path> const& vfs_ini_list);

#endif // _VFS_INIT_H_
