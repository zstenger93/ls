#include "../includes/ls.h"

int main(int argc, char **argv) {
  int exit_status = 0, len = 0, folder_count = 0, y = 1, x = 1;
  t_flags flags;
  char **files = malloc((argc + 1) * sizeof(char *));

  for (; len < argc; len++) {
    files[len] = NULL;
  }
  ft_memset(&flags, 0, sizeof(t_flags));

  if (argc == 1) {
    exit_status = ls(".");
  } else {
    exit_status = parse_flags(argc, argv, &flags, files);
    if (exit_status == 0) {
      while (files[x] != NULL) {
        if (files[x][0] != '\t') {
          folder_count++;
        }
        x++;
      }
      if (folder_count > 0) {
        if (folder_count == 1) {
          while (files[y] != NULL) {
            if (files[y][0] != '\t') {
              break;
            }
            y++;
          }
          exit_status = ls_with_flags(&flags, files[y], folder_count);
        } else {
          x = 1;
          while (files[x] != NULL) {
            if (files[x][0] != '\t') {
              write(1, files[x], ft_strlen(files[x]));
              write(1, ":\n", 2);
              ls_with_flags(&flags, files[x], folder_count);
              if (files[x + 1] != NULL)
                write(1, "\n", 1);
            }
            x++;
          }
        }
      } else
        exit_status = ls_with_flags(&flags, ".", folder_count);
    }
    for (int i = 0; i < argc; i++) {
      if (files[i] != NULL) {
        free(files[i]);
      }
    }
    free(files);
    return exit_status;
  }
}