#include "../includes/ls.h"

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

void write_int(int num) {
  char c;
  if (num == 0) {
    return;
  }
  write_int(num / 10);
  c = '0' + num % 10;
  write(1, &c, 1);
}

void bubble_sort_time(struct dirent *arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      struct stat stat1, stat2;
      char path1[1024], path2[1024];
      ft_strlcpy(path1, arr[j]->d_name, sizeof(path1));
      ft_strlcpy(path2, arr[j + 1]->d_name, sizeof(path2));
      stat(path1, &stat1);
      stat(path2, &stat2);
      if (stat1.st_mtime < stat2.st_mtime) {
        struct dirent *temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}
