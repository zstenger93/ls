#include "../../includes/ls.h"

int ls_with_flags(int argc, char **argv, t_flags *flags) {
  DIR *dir;
  struct dirent *entry;

  if ((dir = opendir(".")) == NULL) {
    perror("opendir");
    return DIR_ERR;
  }

  struct dirent *entries[1024];
  int num_entries = 0;

  while ((entry = readdir(dir)) != NULL) {
    if (flags->a || entry->d_name[0] != '.') {
      entries[num_entries] = malloc(sizeof(struct dirent));
      ft_memcpy(entries[num_entries], entry, sizeof(struct dirent));
      num_entries++;
    }
  }
  closedir(dir);

  bubble_sort(entries, num_entries);

  if (flags->a) {
    for (int i = 0; i < num_entries; i++) {
      write(1, entries[i]->d_name, ft_strlen(entries[i]->d_name));
      write(1, "\n", 1);
      free(entries[i]);
    }
  } else if (flags->l) {
    for (int i = 0; i < num_entries; i++) {
      long_format(entries[i]);
      free(entries[i]);
    }
  }

  (void)argc;
  (void)argv;

  return 0;
}
