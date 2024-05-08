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
#define BOLD_YELLOW "\x1b[33;1m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[96m"
#define WHITE "\x1b[37m"
#define COLOR_RESET "\x1b[0m"

#define RED_X RED "x" COLOR_RESET
#define YELLOW_R YELLOW "r" COLOR_RESET
#define GREEN_W GREEN "w" COLOR_RESET

#define FOLDER_COLOR BLUE
#define FILE_COLOR WHITE
#define EXECUTABLE_COLOR BOLD_YELLOW
#define SYMLINK_COLOR CYAN

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
#define DIR_ERR 2
#define NONEXISTENT_ERR 2
#define INVALID_FLAG 2

#define HELP 66

typedef struct s_flags {
  int a;
  int r;
  int R;
  int l;
  int t;
  int h;
  int p;
  int S;
  int n;
  int g;
  int o;
  int x;
  int help;
  int time_iso;
  int time_full_iso;
  int time_long_iso;
} t_flags;

// parsing
int parse_flags(int argc, char **argv, t_flags *flags, char **files);
void display_error_message(char *argv[], int i, int j);
void set_flags(char arg, t_flags *flags);
int save_file_and_folder_names(char *path, char **files, int index);

// simple ls
int ls(const char *path, t_flags *flags, char *files);
void write_colored_filename(struct stat entryStat, char *filename,
                            t_flags *flags);

// ls with flags and directories
int ls_with_flags(t_flags *flags, char *files, int folder_count);
int read_and_sort_directory(DIR *dir, struct s_flags *flags,
                            struct dirent *entries[], char *files);
void print_entries(struct dirent *entries[], int num_entries, t_flags *flags);
int process_single_folder_argument(t_flags *flags, char **files);
int process_multiple_folder_argument(t_flags *flags, char **files,
                                      int folder_count);
void display_help();

// ls -l
void long_format(struct dirent *entry, t_flags *flags);
void readable_file_size(double size, t_flags *flags);
void write_file_permissions(struct stat fileStat);
void write_owner_and_group(struct stat fileStat, t_flags *flags);
void write_timestamp(struct stat fileStat, t_flags *flags);
char get_file_type(struct stat fileStat);
void get_date_str(const char *time, char *month_str, char *day_str);
void write_iso(const char *month_str, const char *day_str, const char *time);
void write_long_iso(const char *time, const char *month_str,
                    const char *day_str);
void write_full_iso(struct stat fileStat, char *time, char *month_str,
                    char *day_str);
void print_filename_with_color(struct stat fileStat, char *entry_name,
                               t_flags *flags);
void print_symbolic_link_target(struct dirent *entry, struct stat fileStat);

// ls -t
void bubble_sort_time(struct dirent *arr[], int n);

// ls -r
void reverse_entries(struct dirent *entries[], int num_entries);

// ls -R
void print_directory_contents_recursively(t_flags *flags, const char *dir_path,
                                          int folder_count);
void construct_path(char *path, const char *dir_path, const char *entry_name);

// ls -S
void bubble_sort_size(struct dirent *arr[], int n);

// utils
void write_int(int num);
int count_folders(char **files);
void free_files(char **files, int len);
void bubble_sort(struct dirent *arr[], int n);
void int_to_str(int int_size, char *size_str);
int ft_strcasecmp(const char *s1, const char *s2);

#endif