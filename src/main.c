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
    if (exit_status == 0 && exit_status != HELP) {
      folder_count = count_folders(files);
      if (folder_count > 0) {
        if (folder_count == 1) {
          exit_status = process_single_folder_argument(&flags, files);
        } else {
          exit_status = process_multiple_folder_argument(&flags, files, folder_count);
        }
      } else
        exit_status = ls_with_flags(&flags, ".", folder_count);
    }
  }
  free_files(files, len);
  if (exit_status == HELP) {
    exit_status = 0;
    display_help();
  }
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

int process_multiple_folder_argument(t_flags *flags, char **files,
                                      int folder_count) {
  int x = 1, exit_status = 0;
  while (files[x] != NULL) {
    if (files[x][0] != '\t') {
      write(1, files[x], ft_strlen(files[x]));
      write(1, ":\n", 2);
      exit_status = ls_with_flags(flags, files[x], folder_count);
      if (files[x + 1] != NULL)
        write(1, "\n", 1);
    }
    x++;
  }
  return exit_status;
}

void display_help() {
  write(1, "\x1b[33mUsage:\x1b[0m\n", 17);
  write(1, "      ls [OPTIONS]... [FILE]...\n\n", 32);
  write(1, "\x1b[33mARGS:\x1b[0m\n", 15);
  write(1, "      <FILE>...    [default: .]\n\n", 33);
  write(1, "\x1b[33mOPTIONS:\x1b[0m\n", 18);
  write(1,
        "  -a, --all                  do not ignore entries starting with .\n",
        67);
  write(1, "  -l                         use a long listing format\n", 55);
  write(1,
        "  -h, --human-readable       with -l and/or -s, print human readable "
        "sizes\n",
        76);
  write(1, "  -r, --reverse              reverse order while sorting\n", 57);
  write(1, "  -R, --recursive            list subdirectories recursively\n",
        62);
  write(
      1,
      "  -t                         sort by modification time, newest first\n",
      70);
  write(1, "  -S                         sort by file size, largest first\n",
        63);
  write(1,
        "  -n, --numeric-uid-gid      like -l, but list numeric user and group "
        "IDs\n",
        75);
  write(1, "  -g                         like -l, but do not list owner\n", 60);
  write(1,
        "  -o                         like -l, but do not list group "
        "information\n",
        73);
  write(1, "  -p, --indicator-style=slash append / indicator to directories\n",
        65);
  write(1,
        "  -x                         list entries by lines instead of by "
        "columns\n",
        74);
}