#include "../includes/ls.h"

int main(int argc, char **argv) {
  int exit_status = 0, len = 0;
  t_flags flags;
  char **files = malloc((argc + 1) * sizeof(char *));
  int folder_count = 0;

  for (; len < argc; len++) {
    files[len] = NULL;
  }
  ft_memset(&flags, 0, sizeof(t_flags));

  if (argc == 1) {
    exit_status = ls(".");
  } else {
    exit_status = parse_flags(argc, argv, &flags, files);
    if (exit_status == 0) {
      int x = 1;
      while (files[x] != NULL) {
        if (files[x][0] != '\t') {
          folder_count++;
        }
        x++;
      }
      if (folder_count > 0) {
        if (folder_count == 1)
          exit_status = ls_with_flags(argc, argv, &flags, files[x - 1]);
        else {
          x = 1;
          while (files[x] != NULL) {
            if (files[x][0] != '\t') {
              write(1, files[x], ft_strlen(files[x]));
              write(1, ":\n", 2);
              ls_with_flags(argc, argv, &flags, files[x]);
              if (files[x + 2] != NULL)
                write(1, "\n", 1);
            }
            x++;
          }
        }
      } else
        exit_status = ls_with_flags(argc, argv, &flags, ".");
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