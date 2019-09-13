#pragma once
#include <pwd.h>
#include <grp.h>
#include <ctype.h>

/* declaration for ugid_function.c*/
char * userNameFromId(uid_t uid);

uid_t userIdFromName(const char * name);

char * groupNameFromId(gid_t gid);

gid_t groupIdFromName(const char * name);


