#include "../includes/ls.h"

int parse_flags(int argc, char **argv, t_flags *flags, char **files) {
  int i, j;
  char *valid_flags = "arlRt";

  for (i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      j = 1;
      while (argv[i][j]) {
        if (ft_pf_strchr(valid_flags, argv[i][j])) {
          if (argv[i][j] == 'a')
            flags->a = 1;
          else if (argv[i][j] == 'r')
            flags->r = 1;
          else if (argv[i][j] == 'R')
            flags->R = 1;
          else if (argv[i][j] == 'l')
            flags->l = 1;
          else if (argv[i][j] == 't') // always goes before -r
            flags->t = 1;
        } else {
          write(2, ERROR_TEXT_0, ft_strlen(ERROR_TEXT_0));
          write(2, &argv[i][j], 1);
          write(2, ERROR_TEXT_1, ft_strlen(ERROR_TEXT_1));
          write(2, &argv[i][j], 1);
          write(2, ERROR_TEXT_2, ft_strlen(ERROR_TEXT_2));
          write(2, &argv[i][j], 1);
          write(2, ERROR_TEXT_3, ft_strlen(ERROR_TEXT_3));
          write(2, HELP_TEXT, ft_strlen(HELP_TEXT));
          return INVALID_FLAG;
        }
        j++;
      }
      files[i] = ft_strdup("\t");
    } else {
      struct stat path_stat;
      if (stat(argv[i], &path_stat) == -1) {
        write(1, "ls: No such file or directory (os error 2).\n", 44);
        return NONEXISTENT_ERR;
      }
      if (S_ISDIR(path_stat.st_mode)) {
        files[i] = ft_strdup(argv[i]);
      } else if (access(argv[i], F_OK) != -1) {
        files[i] = ft_strdup(argv[i]);
      }
    }
  }
  return 0;
}