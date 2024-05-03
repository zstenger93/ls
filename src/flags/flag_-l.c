#include "../../includes/ls.h"

/*
    symbolic link display can be tested with:
    touch test1 && nl -s test1 test2
*/
void long_format(struct dirent *entry) {
  struct stat fileStat;

  if (lstat(entry->d_name, &fileStat) < 0)
    return;

  write_file_permissions(fileStat);
  write(1, " ", 1);

  write_int(fileStat.st_nlink); // number of hard links
  write(1, " ", 1);

  struct passwd *pw = getpwuid(fileStat.st_uid);
  if (pw != NULL) { // name of the file's owner
    write(1, pw->pw_name, ft_strlen(pw->pw_name));
    write(1, " ", 1);
  }

  struct group *gr = getgrgid(fileStat.st_gid);
  if (gr != NULL) { // group name
    write(1, gr->gr_name, ft_strlen(gr->gr_name));
  }
  write(1, "\t", 1);

  readable_file_size(fileStat.st_size);
  write(1, "\t", 1);

  char *time = ctime(&fileStat.st_mtime); // modification time
  time[ft_strlen(time) - 1] = '\0';
  write(1, time, ft_strlen(time));
  write(1, " ", 1);

  char *last_slash = ft_strrchr(entry->d_name, '/');
  char *filename = last_slash ? last_slash + 1 : entry->d_name;
  write(1, filename, ft_strlen(filename));

  if (S_ISLNK(fileStat.st_mode)) {
    char link_target[1024];
    ssize_t len = readlink(entry->d_name, link_target, sizeof(link_target) - 1);
    if (len != -1) {
      link_target[len] = '\0';
      write(1, " -> ", 4);
      write(1, link_target, ft_strlen(link_target));
    }
  }

  write(1, "\n", 1);
}

void write_file_permissions(struct stat fileStat) {
  // file type: 'd' for directory, '-' for regular file
  write(1, (S_ISDIR(fileStat.st_mode)) ? "d" : "-", 1);

  // user permissions: 'r' for read, 'w' for write, 'x' for execute
  write(1, (fileStat.st_mode & S_IRUSR) ? "r" : "-", 1);
  write(1, (fileStat.st_mode & S_IWUSR) ? "w" : "-", 1);
  write(1, (fileStat.st_mode & S_IXUSR) ? "x" : "-", 1);

  // group permissions:
  write(1, (fileStat.st_mode & S_IRGRP) ? "r" : "-", 1);
  write(1, (fileStat.st_mode & S_IWGRP) ? "w" : "-", 1);
  write(1, (fileStat.st_mode & S_IXGRP) ? "x" : "-", 1);

  // other permissions:
  write(1, (fileStat.st_mode & S_IROTH) ? "r" : "-", 1);
  write(1, (fileStat.st_mode & S_IWOTH) ? "w" : "-", 1);
  write(1, (fileStat.st_mode & S_IXOTH) ? "x" : "-", 1);
}

void readable_file_size(double size) {
  const char *units[] = {"B", "KB", "MB", "GB", "TB"};
  int i = 0;

  while (size > 1024) {
    size /= 1024;
    i++;
  }

  int int_size = (int)size;
  char size_str[10];
  int_to_str(int_size, size_str);

  write(1, size_str, ft_strlen(size_str));
  write(1, " ", 1);
  write(1, units[i], ft_strlen(units[i]));
}