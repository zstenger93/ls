#include "../includes/ls.h"

int ls(const char *path, t_flags *flags, char *files) {
  DIR *dir;
  struct dirent *entry;

  if ((dir = opendir(path)) == NULL) {
    perror("opendir");
    return DIR_ERR;
  }

  struct dirent *entries[1024];
  int num_entries = 0;
  while ((entry = readdir(dir)) != NULL) {
    if (flags->a || entry->d_name[0] != '.') {
      entries[num_entries] = malloc(sizeof(struct dirent));
      ft_memcpy(entries[num_entries], entry, sizeof(struct dirent));
      char temp[1024];
      ft_strlcpy(temp, files, sizeof(temp));
      ft_strlcat(temp, "/", sizeof(temp));
      ft_strlcat(temp, entries[num_entries]->d_name, sizeof(temp));
      ft_strlcpy(entries[num_entries]->d_name, temp,
                 sizeof(entries[num_entries]->d_name));

      num_entries++;
    }
  }
  closedir(dir);

  bubble_sort(entries, num_entries);

  for (int i = 0; i < num_entries; i++) {
    if (i > 0) {
      write(1, "  ", 2);
    }
    struct stat entryStat;
    if (stat(entries[i]->d_name, &entryStat) == -1) {
      perror("stat");
      for (int j = 0; j < num_entries; j++) {
        free(entries[j]);
      }
      return PATH_ERR;
    }
    char *last_slash = ft_strrchr(entries[i]->d_name, '/');
    char *filename = last_slash ? last_slash + 1 : entries[i]->d_name;
    if (S_ISDIR(entryStat.st_mode)) {
      write(1, FOLDER_COLOR, ft_strlen(FOLDER_COLOR));
      write(1, filename, ft_strlen(filename));
      write(1, COLOR_RESET, ft_strlen(COLOR_RESET));
    } else if (S_ISREG(entryStat.st_mode)) {
      write(1, FILE_COLOR, ft_strlen(FILE_COLOR));
      write(1, filename, ft_strlen(filename));
      write(1, COLOR_RESET, ft_strlen(COLOR_RESET));
    } else {
      write(1, filename, ft_strlen(filename));
    }
    free(entries[i]);
  }
  write(1, "\n", 1);
  return 0;
}