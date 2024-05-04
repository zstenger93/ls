#include "../includes/ls.h"

int main(int argc, char **argv) {
  t_flags flags;
  int exit_status = 0, len = 0, folder_count = 0;
  char **files = malloc((argc + 1) * sizeof(char *));

  for (; len <= argc; len++)
    files[len] = NULL;
  ft_memset(&flags, 0, sizeof(t_flags));

  if (argc == 1) {
    exit_status = ls(".", &flags, ".");
  } else {
    exit_status = parse_flags(argc, argv, &flags, files);
    if (exit_status == 0) {
      folder_count = count_folders(files);
      if (folder_count > 0) {
        if (folder_count == 1) {
          exit_status = process_single_folder_argument(&flags, files);
        } else {
          process_multiple_folder_argument(&flags, files, folder_count);
        }
      } else
        exit_status = ls_with_flags(&flags, ".", folder_count);
    }
  }
  free_files(files, len);
  return exit_status;
}

int process_single_folder_argument(t_flags *flags, char **files) {
  int y = 1;
  while (files[y] != NULL) {
    if (files[y][0] != '\t')
      break;
    y++;
  }
  return ls_with_flags(flags, files[y], 1);
}

void process_multiple_folder_argument(t_flags *flags, char **files,
                                      int folder_count) {
  int x = 1;
  while (files[x] != NULL) {
    if (files[x][0] != '\t') {
      write(1, files[x], ft_strlen(files[x]));
      write(1, ":\n", 2);
      ls_with_flags(flags, files[x], folder_count);
      if (files[x + 1] != NULL)
        write(1, "\n", 1);
    }
    x++;
  }
}