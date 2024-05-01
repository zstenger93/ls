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

int ft_strcasecmp(const char *s1, const char *s2) {
  while (*s1 && *s2) {
    if (ft_tolower(*s1) != ft_tolower(*s2)) {
      return ft_tolower(*s1) - ft_tolower(*s2);
    }
    s1++;
    s2++;
  }
  return ft_tolower(*s1) - ft_tolower(*s2);
}

void bubble_sort(struct dirent *arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (ft_strcasecmp(arr[j]->d_name, arr[j + 1]->d_name) > 0) {
        struct dirent *temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

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
    write(1, entries[i]->d_name, ft_strlen(entries[i]->d_name));
    write(1, "\n", 1);
    free(entries[i]);
  }

  return 0;
}
