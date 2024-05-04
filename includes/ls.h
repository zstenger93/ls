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

#define RED "\x1b[31m"
#define RED_BOLD "\x1b[1;31m"
#define GREEN "\x1b[32m"
#define BOLD_GREEN "\x1b[32;1m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[96m"
#define WHITE "\x1b[37m"
#define COLOR_RESET "\x1b[0m"

#define RED_X RED "x" COLOR_RESET
#define YELLOW_R YELLOW "r" COLOR_RESET
#define GREEN_W GREEN "w" COLOR_RESET

#define FOLDER_COLOR GREEN
#define FILE_COLOR WHITE

#define ERROR_TEXT_0                                                           \
  RED_BOLD "error:" COLOR_RESET " Found argument '" YELLOW "-"
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

int ls(const char *path, t_flags *flags, char *files);
int parse_flags(int argc, char **argv, t_flags *flags, char **files);
int ls_with_flags(t_flags *flags, char *files, int folder_count);
int read_and_sort_directory(DIR *dir, struct s_flags *flags,
                            struct dirent *entries[], int folder_count,
                            char *files);
void print_entries(struct dirent *entries[], int num_entries);
int process_single_folder_argument(t_flags *flags, char **files);
void process_multiple_folder_argument(t_flags *flags, char **files,
                                      int folder_count);

// ls -l
void long_format(struct dirent *entry);
void readable_file_size(double size);
void write_file_permissions(struct stat fileStat);
void print_filename_with_color(struct stat fileStat, char *entry_name);

// ls -t
void bubble_sort_time(struct dirent *arr[], int n);

// ls -r
void reverse_entries(struct dirent *entries[], int num_entries);

// ls -R
void print_directory_contents_recursively(t_flags *flags, const char *dir_path,
                                          int folder_count);
void construct_path(char *path, const char *dir_path, const char *entry_name);

// UTILS
void write_int(int num);
int count_folders(char **files);
void free_files(char **files, int len);
void bubble_sort(struct dirent *arr[], int n);
void int_to_str(int int_size, char *size_str);
int ft_strcasecmp(const char *s1, const char *s2);

#endif