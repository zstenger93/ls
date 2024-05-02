#include "../../includes/ls.h"

int ls_with_flags(int argc, char **argv, t_flags *flags, char **files) {
  DIR *dir;

  if ((dir = opendir(".")) == NULL) {
    perror("opendir");
    return DIR_ERR;
  }

  struct dirent *entries[1024];
  int num_entries = read_and_sort_directory(dir, flags, entries);

  if (num_entries < 0) {
    return DIR_ERR;
  }

  if (flags->a) { // showing all files
    for (int i = 0; i < num_entries; i++) {
      write(1, entries[i]->d_name, ft_strlen(entries[i]->d_name));
      write(1, "\n", 1);
      free(entries[i]);
    }
  } else if (flags->l) { // long listing format
    for (int i = 0; i < num_entries; i++) {
      long_format(entries[i]);
      free(entries[i]);
    }
  } else if (flags->t) { // order by modification time
    for (int i = 0; i < num_entries; i++) {
      write(1, entries[i]->d_name, ft_strlen(entries[i]->d_name));
      write(1, "  ", 2);
      free(entries[i]);
    }
    write(1, "\n", 1);
  } else if (flags->r) { // reverse order
    for (int i = num_entries - 1; i >= 0; i--) {
      write(1, entries[i]->d_name, ft_strlen(entries[i]->d_name));
      write(1, "  ", 2);
      free(entries[i]);
    }
    write(1, "\n", 1);
  } else if (flags->R) { // recursive directory listing
    (void)files;
    ls(".");
    print_directory_contents_recursively(".");
    for (int i = 0; i < num_entries; i++) {
      free(entries[i]);
    }
  }

  (void)argc;
  (void)argv;

  return 0;
}


/*
    read and sort the directory entries and
    based on the flags provided sort them
    in order
*/
int read_and_sort_directory(DIR *dir, struct s_flags *flags,
                            struct dirent *entries[]) {
  struct dirent *entry;
  int num_entries = 0;

  while ((entry = readdir(dir)) != NULL) {
    if (flags->a || entry->d_name[0] != '.') {
      entries[num_entries] = malloc(sizeof(struct dirent));
      ft_memcpy(entries[num_entries], entry, sizeof(struct dirent));
      num_entries++;
    }
  }
  closedir(dir);

  if (flags->t) {
    bubble_sort_time(entries, num_entries);
  } else {
    bubble_sort(entries, num_entries);
  }

  return num_entries;
}