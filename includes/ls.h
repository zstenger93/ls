#ifndef LS_H
#define LS_H

#include "../libft/includes/libft.h"

#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/xattr.h>
#include <time.h>

#define RED "\x1b[1;31m"
#define GREEN "\x1b[32m"
#define BOLD_GREEN "\x1b[32;1m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define BOLD_CYAN "\x1b[96;1m"
#define COLOR_RESET "\x1b[0m"

#define ERROR_TEXT_0 RED "error:" COLOR_RESET " Found argument '" YELLOW "-"
#define ERROR_TEXT_1                                                           \
  COLOR_RESET "' which wasn't expected, or isn't valid in this context\n\nIf " \
              "you tried "                                                     \
              "to supply `-"
#define ERROR_TEXT_2 "` as a value rather than a flag, use `-- -"
#define ERROR_TEXT_3                                                           \
  "`\n\nUSAGE:\n    ls [OPTIONS] [--] [FILE]...\n\nFor more information try"
#define HELP_TEXT GREEN " --help" COLOR_RESET "\n"

#define PATH_ERR 2
#define DIR_ERR 3
#define NONEXISTENT_ERR 2

#define INVALID_FLAG 2

typedef struct s_flags {
  int a;
  int r;
  int R;
  int l;
  int t;
} t_flags;

int ls(const char *path);
int parse_flags(int argc, char **argv, t_flags *flags, char **files);
int ls_with_flags(int argc, char **argv, t_flags *flags, char **files);
int read_and_sort_directory(DIR *dir, struct s_flags *flags,
                            struct dirent *entries[]);

// ls -l
void long_format(struct dirent *entry);
void readable_file_size(double size);
void write_file_permissions(struct stat fileStat);

// ls -t
void bubble_sort_time(struct dirent *arr[], int n);

// ls -r

// ls -R
void print_directory_contents_recursively(const char *dir_path);
void construct_path(char *path, const char *dir_path, const char *entry_name);

// UTILS
void write_int(int num);
void bubble_sort(struct dirent *arr[], int n);
int ft_strcasecmp(const char *s1, const char *s2);

#endif