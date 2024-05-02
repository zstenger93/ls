#include "../../includes/ls.h"

void print_directory_contents_recursively(const char *dir_path) {
  DIR *dir = opendir(dir_path);

  if (dir == NULL) {
    perror("Unable to open directory");
    return;
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    struct stat path_stat;
    stat(entry->d_name, &path_stat);

    if (S_ISDIR(path_stat.st_mode) && ft_strncmp(entry->d_name, ".", 1) != 0 &&
        ft_strncmp(entry->d_name, "..", 2) != 0) {
      char path[1024];

      construct_path(path, dir_path, entry->d_name);

      struct stat path_stat_check;
      stat(path, &path_stat_check);

      if (S_ISDIR(path_stat_check.st_mode)) {
        write(1, "\n", 1);
        write(1, path, ft_strlen(path));
        write(1, ":\n", 2);
        ls(path);
        print_directory_contents_recursively(path);
      }
    }
  }
  closedir(dir);
}

/*
    always updating the and constructing the
    current path for the recursive call
*/
void construct_path(char *path, const char *dir_path, const char *entry_name) {
  int i = 0;
  while (dir_path[i] != '\0') {
    path[i] = dir_path[i];
    i++;
  }
  path[i] = '/';
  i++;
  int j = 0;
  while (entry_name[j] != '\0') {
    path[i + j] = entry_name[j];
    j++;
  }
  path[i + j] = '\0';
}