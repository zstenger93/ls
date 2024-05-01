#include "../includes/ls.h"

int main(int argc, char **argv) {
  int exit_status = 0;

  if (argc == 1) {
    exit_status = ls();
  } else {
    exit_status = ls_with_flags(argc, argv);
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
      printf("%s\n", entry->d_name);
    }
  }
  closedir(dir);
  return 0;
}

int ls_with_flags(int argc, char **argv) {
  (void)argc;
    (void)argv;
  return 0;
}