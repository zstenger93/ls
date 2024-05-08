#include "../../includes/ls.h"

int ls_with_flags(t_flags *flags, char *files, int folder_count) {
  DIR *dir;
  if ((dir = opendir(files)) == NULL)
    return perror("opendir"), DIR_ERR;

  struct dirent *entries[1024];
  int num_entries = read_and_sort_directory(dir, flags, entries, files);

  if (num_entries < 0)
    return DIR_ERR;
  // order by modification time, always goes before -r
  if (flags->t && !flags->a && !flags->r && !flags->R && !flags->l)
    print_entries(entries, num_entries, flags);
  if (flags->r && !flags->a && !flags->t && !flags->R && !flags->l)
    print_entries(entries, num_entries, flags); // reverse order
  if (flags->a && !flags->l && !flags->R)       // showing all files
    print_entries(entries, num_entries, flags);
  if (flags->l || flags->n || flags->o || flags->g) // long listing format
    for (int i = 0; i < num_entries; i++)
      long_format(entries[i], flags);
  if (flags->R) { // recursive directory listing
    if ((folder_count == 0 && !flags->l) || !flags->l)
      ls(files, flags, files);
	int i = 0;
    if (i <= folder_count)
      print_directory_contents_recursively(flags, files, folder_count);
	i++;
  } // default alphabetical order
  if (!flags->a && !flags->r && !flags->R && !flags->l && !flags->t)
    print_entries(entries, num_entries, flags);
  for (int i = 0; i < num_entries; i++)
    free(entries[i]);
  return 0;
}

/*
    read and sort the directory entries and
    based on the flags provided sort them
    in order
    default: alphabetical order
    -t: modification time <- awlays goes before -r
    -r: reverse order
    -S: order by size
*/
int read_and_sort_directory(DIR *dir, struct s_flags *flags,
                            struct dirent *entries[], char *files) {
  struct dirent *entry;
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
  if (flags->S) {
    bubble_sort_size(entries, num_entries);
  } else if (flags->t) {
    bubble_sort_time(entries, num_entries);
  } else
    bubble_sort(entries, num_entries);
  if (flags->r)
    reverse_entries(entries, num_entries);
  return num_entries;
}

void reverse_entries(struct dirent *entries[], int num_entries) {
  for (int i = 0; i < num_entries / 2; i++) {
    struct dirent *temp = entries[i];
    entries[i] = entries[num_entries - i - 1];
    entries[num_entries - i - 1] = temp;
  }
}

void print_entries(struct dirent *entries[], int num_entries, t_flags *flags) {
  for (int i = 0; i < num_entries; i++) {
    char *last_slash = ft_strrchr(entries[i]->d_name, '/');
    char *filename = last_slash ? last_slash + 1 : entries[i]->d_name;
    struct stat fileStat;
    if (lstat(entries[i]->d_name, &fileStat) == -1) {
      for (int j = 0; j < num_entries; j++)
        free(entries[j]);
      return perror("stat");
    }
    print_filename_with_color(fileStat, filename, flags);
    write(1, !flags->x ? "  " : "\n", 2);
  }
  write(1, !flags->x ? "\n" : "", 1);
}
