#include "../../includes/ls.h"

void write_int(int num) {
  char c;
  if (num == 0) {
    return;
  }
  write_int(num / 10);
  c = '0' + num % 10;
  write(1, &c, 1);
}

void long_format(struct dirent *entry) {
  struct stat fileStat;

  if (stat(entry->d_name, &fileStat) < 0)
    return;

  // Write the file type: 'd' for directory, '-' for regular file
  write(1, (S_ISDIR(fileStat.st_mode)) ? "d" : "-", 1);

  // Write the user permissions: 'r' for read, 'w' for write, 'x' for execute
  write(1, (fileStat.st_mode & S_IRUSR) ? "r" : "-", 1);
  write(1, (fileStat.st_mode & S_IWUSR) ? "w" : "-", 1);
  write(1, (fileStat.st_mode & S_IXUSR) ? "x" : "-", 1);

  // Write the group permissions: 'r' for read, 'w' for write, 'x' for execute
  write(1, (fileStat.st_mode & S_IRGRP) ? "r" : "-", 1);
  write(1, (fileStat.st_mode & S_IWGRP) ? "w" : "-", 1);
  write(1, (fileStat.st_mode & S_IXGRP) ? "x" : "-", 1);

  // Write the other permissions: 'r' for read, 'w' for write, 'x' for execute
  write(1, (fileStat.st_mode & S_IROTH) ? "r" : "-", 1);
  write(1, (fileStat.st_mode & S_IWOTH) ? "w" : "-", 1);
  write(1, (fileStat.st_mode & S_IXOTH) ? "x" : "-", 1);

  write(1, " ", 1);

  // Write the number of hard links
  write_int(fileStat.st_nlink);

  write(1, " ", 1);

  // Write the user ID of the file's owner
  struct passwd *pw = getpwuid(fileStat.st_uid);
  if (pw != NULL) {
    write(1, pw->pw_name, ft_strlen(pw->pw_name));
  }

  write(1, " ", 1);

  // Write the group name of the file
  struct group *gr = getgrgid(fileStat.st_gid);
  if (gr != NULL) {
    write(1, gr->gr_name, ft_strlen(gr->gr_name));
  }

  write(1, "\t", 1);

  // Write the size of the file in a readable format
  readable_file_size(fileStat.st_size);

  write(1, "\t", 1);

  // Write the modification time of the file
  char *time = ctime(&fileStat.st_mtime);
  time[ft_strlen(time) - 1] = '\0';
  write(1, time, ft_strlen(time));

  write(1, " ", 1);

  // Write the name of the file
  write(1, entry->d_name, ft_strlen(entry->d_name));

  write(1, "\n", 1);
}

void readable_file_size(double size) {
  const char *units[] = {"B", "KB", "MB", "GB", "TB"};
  int i = 0;

  while (size > 1024) {
    size /= 1024;
    i++;
  }

  int int_size = (int)size;

  // Convert the integer size to a string
  char size_str[10];
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

  // Write the size and unit to the terminal
  write(1, size_str, ft_strlen(size_str));
  write(1, " ", 1);
  write(1, units[i], ft_strlen(units[i]));
}