#include "../../includes/ls.h"

int ls_with_flags(int argc, char **argv, t_flags *flags) {
  if (flags->a) {
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(".")) == NULL) {
      perror("opendir");
      return DIR_ERR;
    }
    while ((entry = readdir(dir)) != NULL) {
      write(1, entry->d_name, ft_strlen(entry->d_name));
      write(1, "\n", 1);
    }
    closedir(dir);
  }

  (void)argc;
  (void)argv;

  return 0;
}