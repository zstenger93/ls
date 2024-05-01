#include "../includes/ls.h"

int main(int argc, char **argv) {
  int exit_status = 0;
  t_flags flags;

  ft_memset(&flags, 0, sizeof(t_flags));

  if (argc == 1) {
    exit_status = ls();
  } else {
    exit_status = parse_flags(argc, argv, &flags);
    if (exit_status == 0)
      exit_status = ls_with_flags(argc, argv, &flags);
  }
  return exit_status;
}

int ls() {
  DIR *dir;
  struct dirent *entry;

  if ((dir = opendir(".")) == NULL) {
    perror("opendir");
    return DIR_ERR;
  }
  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_name[0] != '.') {
      write(1, entry->d_name, ft_strlen(entry->d_name));
      write(1, "\n", 1);
    }
  }
  closedir(dir);
  return 0;
}

int parse_flags(int argc, char **argv, t_flags *flags) {
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
          else if (argv[i][j] == 't')
            flags->t = 1;
        } else {
          write(2, RED, ft_strlen(RED));
          write(2, "error:", 6);
          write(2, COLOR_RESET, ft_strlen(COLOR_RESET));
          write(2, " Found argument '-", 18);
          write(2, &argv[i][j], 1);
          write(2,
                "' which wasn't expected, or isn't valid in this context\n\n",
                57);
          write(2, "If you tried to supply `-", 24);
          write(2, &argv[i][j], 1);
          write(2, "` as a value rather than a flag, use `-- -", 43);
          write(2, &argv[i][j], 1);
          write(2,
                "`\n\nUSAGE:\n    ls [OPTIONS] [--] [FILE]...\n\nFor more "
                "information try ",
                67);
          write(2, GREEN, ft_strlen(GREEN));
          write(2, " --help", 7);
          write(2, COLOR_RESET, ft_strlen(COLOR_RESET));
          write(2, "\n", 1);
          return INVALID_FLAG;
        }
        j++;
      }
    }
  }
  return 0;
}