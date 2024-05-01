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
