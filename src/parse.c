#include "../includes/ls.h"

int parse_flags(int argc, char **argv, t_flags *flags, char **files) {
  int i, j;
  char *valid_flags = "arlRthpS";

  for (i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      j = 1;
      while (argv[i][j]) {
        if (ft_pf_strchr(valid_flags, argv[i][j])) {
          set_flags(argv[i][j], flags);
        } else
          return display_error_message(argv, i, j), INVALID_FLAG;
        j++;
      }
      files[i] = ft_strdup("\t");
    } else {
      if (save_file_and_folder_names(argv[i], files, i) == NONEXISTENT_ERR)
        return NONEXISTENT_ERR;
    }
  }
  return 0;
}

void set_flags(char arg, t_flags *flags) {
  switch (arg) {
  case 'a':
    flags->a = 1;
    break;
  case 'r':
    flags->r = 1;
    break;
  case 'R':
    flags->R = 1;
    break;
  case 'l':
    flags->l = 1;
    break;
  case 't':
    flags->t = 1;
    break;
  case 'h':
    flags->h = 1;
    break;
  case 'p':
    flags->p = 1;
    break;
  case 'S':
    flags->S = 1;
    break;
  }
}

void display_error_message(char *argv[], int i, int j) {
  write(2, ERROR_TEXT_0, ft_strlen(ERROR_TEXT_0));
  write(2, &argv[i][j], 1);
  write(2, ERROR_TEXT_1, ft_strlen(ERROR_TEXT_1));
  write(2, &argv[i][j], 1);
  write(2, ERROR_TEXT_2, ft_strlen(ERROR_TEXT_2));
  write(2, &argv[i][j], 1);
  write(2, ERROR_TEXT_3, ft_strlen(ERROR_TEXT_3));
  write(2, HELP_TEXT, ft_strlen(HELP_TEXT));
}

// saving the file and folder names for later access
int save_file_and_folder_names(char *path, char **files, int index) {
  struct stat path_stat;
  if (stat(path, &path_stat) == -1) {
    write(2, "ls: ", 4);
    write(2, path, ft_strlen(path));
    write(1, ": No such file or directory (os error 2).\n\n", 43);
    return NONEXISTENT_ERR;
  }
  if (S_ISDIR(path_stat.st_mode) || access(path, F_OK) != -1)
    files[index] = ft_strdup(path);
  return 0;
}