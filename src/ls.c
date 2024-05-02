#include "../includes/ls.h"

int ls() {
  DIR *dir;
  struct dirent *entry;

  if ((dir = opendir(".")) == NULL) {
    perror("opendir");
    return DIR_ERR;
  }

  struct dirent *entries[1024];
  int num_entries = 0;
  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_name[0] != '.') {
      entries[num_entries] = malloc(sizeof(struct dirent));
      ft_memcpy(entries[num_entries], entry, sizeof(struct dirent));
      num_entries++;
    }
  }
  closedir(dir);

  bubble_sort(entries, num_entries);

  for (int i = 0; i < num_entries; i++) {
    if (i > 0) {
      write(1, "  ", 2);
    }
    write(1, entries[i]->d_name, ft_strlen(entries[i]->d_name));
    free(entries[i]);
  }
  write(1, "\n", 1);
  return 0;
}