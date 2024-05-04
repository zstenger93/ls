#include "../../includes/ls.h"

/*
    symbolic link display can be tested with:
    touch test1 && nl -s test1 test2
*/
void long_format(struct dirent *entry, t_flags *flags) {
  struct stat fileStat;

  if (lstat(entry->d_name, &fileStat) < 0)
    return;

  write_file_permissions(fileStat);
  write(1, " ", 1);

  write_int(fileStat.st_nlink); // number of hard links
  write(1, " ", 1);

  struct passwd *pw = getpwuid(fileStat.st_uid); // name of the file's owner
  if (pw != NULL) {
    write(1, pw->pw_name, ft_strlen(pw->pw_name));
    write(1, " ", 1);
  }

  struct group *gr = getgrgid(fileStat.st_gid); // group name
  if (gr != NULL)
    write(1, gr->gr_name, ft_strlen(gr->gr_name));
  write(1, "\t", 1);

  readable_file_size(fileStat.st_size, flags);

  char *time = ctime(&fileStat.st_mtime); // modification time
  time[ft_strlen(time) - 1] = '\0';
  write(1, time, ft_strlen(time));
  write(1, " ", 1);

  print_filename_with_color(fileStat, entry->d_name, flags);

  if (S_ISLNK(fileStat.st_mode)) { // symbolic link
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
  char type = get_file_type(fileStat);
  write(1, &type, 1);

  // user permissions: 'r' for read, 'w' for write, 'x' for execute
  write(1, (fileStat.st_mode & S_IRUSR) ? YELLOW_R : "-",
        ft_strlen((fileStat.st_mode & S_IRUSR) ? YELLOW_R : "-"));
  write(1, (fileStat.st_mode & S_IWUSR) ? GREEN_W : "-",
        ft_strlen((fileStat.st_mode & S_IWUSR) ? GREEN_W : "-"));
  write(1, (fileStat.st_mode & S_IXUSR) ? RED_X : "-",
        ft_strlen((fileStat.st_mode & S_IXUSR) ? RED_X : "-"));

  // group permissions:
  write(1, (fileStat.st_mode & S_IRGRP) ? YELLOW_R : "-",
        ft_strlen((fileStat.st_mode & S_IRGRP) ? YELLOW_R : "-"));
  write(1, (fileStat.st_mode & S_IWGRP) ? GREEN_W : "-",
        ft_strlen((fileStat.st_mode & S_IWGRP) ? GREEN_W : "-"));
  write(1, (fileStat.st_mode & S_IXGRP) ? RED_X : "-",
        ft_strlen((fileStat.st_mode & S_IXGRP) ? RED_X : "-"));

  // other permissions:
  write(1, (fileStat.st_mode & S_IROTH) ? YELLOW_R : "-",
        ft_strlen((fileStat.st_mode & S_IROTH) ? YELLOW_R : "-"));
  write(1, (fileStat.st_mode & S_IWOTH) ? GREEN_W : "-",
        ft_strlen((fileStat.st_mode & S_IWOTH) ? GREEN_W : "-"));
  write(1, (fileStat.st_mode & S_IXOTH) ? RED_X : "-",
        ft_strlen((fileStat.st_mode & S_IXOTH) ? RED_X : "-"));
}

char get_file_type(struct stat fileStat) {
  if (S_ISREG(fileStat.st_mode)) {
    return '-'; // regular file
  } else if (S_ISDIR(fileStat.st_mode)) {
    return 'd'; // directory
  } else if (S_ISCHR(fileStat.st_mode)) {
    return 'c'; // character device
  } else if (S_ISBLK(fileStat.st_mode)) {
    return 'b'; // block device
  } else if (S_ISFIFO(fileStat.st_mode)) {
    return 'p'; // FIFO (named pipe)
  } else if (S_ISLNK(fileStat.st_mode)) {
    return 'l'; // symbolic link
  } else if (S_ISSOCK(fileStat.st_mode)) {
    return 's'; // socket
  } else {
    return '?'; // unknown
  }
}

void readable_file_size(double size, t_flags *flags) {
  const char *units[] = {"B", "KB", "MB", "GB", "TB"};
  int i = 0;

  while (size > 1024) {
    size /= 1024;
    i++;
  }

  int int_size = (int)size;
  char size_str[50];
  int_to_str(int_size, size_str);
  if (flags->h) { // human readable format
    write(1, size_str, ft_strlen(size_str));
    write(1, " ", 1);
    write(1, units[i], ft_strlen(units[i]));
    write(1, "\t", 1);
  } else { // normal
    write(1, size_str, ft_strlen(size_str));
    write(1, "\t", 1);
  }
}

void print_filename_with_color(struct stat fileStat, char *entry_name,
                               t_flags *flags) {
  char *last_slash = ft_strrchr(entry_name, '/');
  char *filename = last_slash ? last_slash + 1 : entry_name;

  if (S_ISDIR(fileStat.st_mode)) {
    write(1, FOLDER_COLOR, ft_strlen(FOLDER_COLOR));
    write(1, filename, ft_strlen(filename));
    if (flags->p)
      write(1, "/", 1);
    write(1, COLOR_RESET, ft_strlen(COLOR_RESET));
  } else if (S_ISREG(fileStat.st_mode)) {
    if (fileStat.st_mode & S_IXUSR) {
      write(1, EXECUTABLE_COLOR, ft_strlen(EXECUTABLE_COLOR));
      write(1, filename, ft_strlen(filename));
      write(1, COLOR_RESET, ft_strlen(COLOR_RESET));
    } else {
      write(1, FILE_COLOR, ft_strlen(FILE_COLOR));
      write(1, filename, ft_strlen(filename));
      write(1, COLOR_RESET, ft_strlen(COLOR_RESET));
    }
  } else if (S_ISLNK(fileStat.st_mode)) {
    write(1, SYMLINK_COLOR, ft_strlen(SYMLINK_COLOR));
    write(1, filename, ft_strlen(filename));
    write(1, COLOR_RESET, ft_strlen(COLOR_RESET));
  } else
    write(1, filename, ft_strlen(filename));
}