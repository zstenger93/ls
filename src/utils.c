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
  if (num == 0)
    return;
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
      lstat(path1, &stat1);
      lstat(path2, &stat2);

      int time_cmp = stat1.st_mtime - stat2.st_mtime;
      if (time_cmp == 0) {
#ifdef __APPLE__
        time_cmp = stat1.st_mtimespec.tv_nsec - stat2.st_mtimespec.tv_nsec;
#else
        time_cmp = stat1.st_mtim.tv_nsec - stat2.st_mtim.tv_nsec;
#endif
      }
      if (time_cmp < 0) {
        struct dirent *temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

void bubble_sort_size(struct dirent *arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      struct stat stat1, stat2;
      char path1[1024], path2[1024];
      ft_strlcpy(path1, arr[j]->d_name, sizeof(path1));
      ft_strlcpy(path2, arr[j + 1]->d_name, sizeof(path2));
      lstat(path1, &stat1);
      lstat(path2, &stat2);
      if (stat1.st_size < stat2.st_size) {
        struct dirent *temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

// Convert the integer size to a string
void int_to_str(int int_size, char *size_str) {
  int len = 0;

  if (int_size == 0) {
    size_str[len++] = '0';
  } else {
    while (int_size != 0) {
      size_str[len++] = '0' + (int_size % 10);
      int_size /= 10;
    }
  }
  size_str[len] = '\0';

  // Reverse the size string
  for (int i = 0; i < len / 2; i++) {
    char temp = size_str[i];
    size_str[i] = size_str[len - i - 1];
    size_str[len - i - 1] = temp;
  }
}

int count_folders(char **files) {
  int folder_count = 0;
  int x = 1;

  while (files[x] != NULL) {
    if (files[x][0] != '\t')
      folder_count++;
    x++;
  }

  return folder_count;
}

void free_files(char **files, int len) {
  for (int i = 0; i < len; i++) {
    if (files[i] != NULL)
      free(files[i]);
  }
  free(files);
}
