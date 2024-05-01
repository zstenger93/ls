#ifndef LS_H
#define LS_H

#include "../libft/includes/libft.h"

#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <glob.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <sys/acl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <time.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define BOLD_GREEN "\x1b[32;1m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define BOLD_CYAN "\x1b[96;1m"
#define COLOR_RESET "\x1b[0m"

#define FLAG_ERR 1
#define PATH_ERR 2
#define DIR_ERR 3
#define FILE_ERR 4
#define MEM_ERR 5
#define FILE_ACCESS_ERR 6
#define NONEXISTENT_ERR 7

#define INVALID_FLAG 2

#define IS_NONEXISTENT 8
#define IS_DIR 9
#define IS_NOT_DIR 10
#define IS_FILE 11
#define IS_NOT_READABLE 12
#define IS_LINK 13

#define IS_USER 14
#define IS_GROUP 15
#define IS_OTHER 16

typedef struct s_flags {
    int a;
    int r;
    int R;
    int l;
    int t;
} t_flags;

int ls();
int parse_flags(int argc, char **argv, t_flags *flags);
int ls_with_flags(int argc, char **argv, t_flags *flags);

#endif