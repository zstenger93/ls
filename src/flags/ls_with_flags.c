#include "../../includes/ls.h"

int ls_with_flags(t_flags *flags, char *files) {
  DIR *dir;

  if ((dir = opendir(files)) == NULL) {
    perror("opendir");
    return DIR_ERR;
  }

  struct dirent *entries[1024];
  int num_entries = read_and_sort_directory(dir, flags, entries);

  if (num_entries < 0) {
    return DIR_ERR;
  }
  // order by modification time, always goes before -r
  if (flags->t && !flags->a && !flags->r && !flags->R && !flags->l) {
    print_and_free_entries(entries, num_entries);
  } // reverse order
  if (flags->r && !flags->a && !flags->t && !flags->R && !flags->l) {
    print_and_free_entries(entries, num_entries);
  } // showing all files
  if (flags->a && !flags->l && !flags->R) {
    print_and_free_entries(entries, num_entries);
  } // long listing format
  if (flags->l) {
    for (int i = 0; i < num_entries; i++) {
      long_format(entries[i]);
      free(entries[i]);
    }
  } // recursive directory listing
  if (flags->R) {
    ls(files);
    print_directory_contents_recursively(flags, files);
    for (int i = 0; i < num_entries; i++) {
      free(entries[i]);
    }
  } // default alphabetical order
  if (!flags->a && !flags->r && !flags->R && !flags->l && !flags->t) {
    print_and_free_entries(entries, num_entries);
  }
  return 0;
}

/*
    read and sort the directory entries and
    based on the flags provided sort them
    in order
    default: alphabetical order
    -t: modification time <- awlays goes before -r
    -r: reverse order
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
  if (flags->r) {
    reverse_entries(entries, num_entries);
  }
  return num_entries;
}

void reverse_entries(struct dirent *entries[], int num_entries) {
  for (int i = 0; i < num_entries / 2; i++) {
    struct dirent *temp = entries[i];
    entries[i] = entries[num_entries - i - 1];
    entries[num_entries - i - 1] = temp;
  }
}

void print_and_free_entries(struct dirent *entries[], int num_entries) {
  for (int i = 0; i < num_entries; i++) {
    write(1, entries[i]->d_name, ft_strlen(entries[i]->d_name));
    write(1, "  ", 2);
    free(entries[i]);
  }
  write(1, "\n", 1);
}