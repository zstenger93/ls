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
