#include "../includes/ls.h"

int main(int argc, char **argv) {
  int exit_status = 0;
  t_flags flags;
  char **files = malloc(argc * sizeof(char *));
  for (int i = 0; i < argc; i++) {
    files[i] = NULL;
  }
  ft_memset(&flags, 0, sizeof(t_flags));

  if (argc == 1) {
    exit_status = ls(".");
  } else {
    exit_status = parse_flags(argc, argv, &flags, files);
    if (exit_status == 0)
      exit_status = ls_with_flags(argc, argv, &flags, files);
  }
  for (int i = 0; i < argc; i++) {
    if (files[i] != NULL) {
      free(files[i]);
    }
  }
  free(files);
  return exit_status;
}
