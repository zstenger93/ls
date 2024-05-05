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
  write_owner_and_group(fileStat, flags);
  readable_file_size(fileStat.st_size, flags);
  write_timestamp(fileStat, flags);
  write(1, " ", 1);
  print_filename_with_color(fileStat, entry->d_name, flags);
  print_symbolic_link_target(entry, fileStat);
  write(1, "\n", 1);
}

void write_owner_and_group(struct stat fileStat, t_flags *flags) {
  if (flags->n && !flags->o) {
    if (fileStat.st_uid == 0)
      write(1, "0", 1);
    else
      write_int(fileStat.st_uid); // owner ID
    write(1, " ", 1);
  }
  if (flags->n && !flags->g) {
    if (fileStat.st_uid == 0)
      write(1, "0", 1);
    else
      write_int(fileStat.st_gid); // group ID
  }
  if (!flags->n && !flags->o) {
    struct passwd *pw = getpwuid(fileStat.st_uid); // name of the file's owner
    if (pw != NULL) {
      write(1, pw->pw_name, ft_strlen(pw->pw_name));
      write(1, " ", 1);
    }
  }
  if (!flags->n && !flags->g) {
    struct group *gr = getgrgid(fileStat.st_gid); // group name
    if (gr != NULL)
      write(1, gr->gr_name, ft_strlen(gr->gr_name));
  }
  write(1, "\t", 1);
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
  } else
    return '?'; // unknown
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

/*
    handling different type of time formats in long format
    - default: Day Mon DD HH:MM
    the following can be applied for example as --time-style=full-iso
    - time_iso: MM-DD HH:MM
    - time_full_iso: YYYY-MM-DD HH:MM:SS.000000000 +0000
    - time_long_iso: YYYY-MM-DD HH:MM

*/
void write_timestamp(struct stat fileStat, t_flags *flags) {
  char *time = ctime(&fileStat.st_mtime); // modification time
  time[ft_strlen(time) - 1] = '\0';       // remove newline at the end

  char month_str[3];
  char day_str[3];
  get_date_str(time, month_str, day_str);

  if (flags->time_iso) {
    write_iso(month_str, day_str, time);
  } else if (flags->time_full_iso) {
    write_full_iso(fileStat, time, month_str, day_str);
  } else if (flags->time_long_iso) {
    write_long_iso(time, month_str, day_str);
  } else
    write(1, time, 16);
}

/*
    from the time string, extract the month and day and convert them into number
   strings
*/
void get_date_str(const char *time, char *month_str, char *day_str) {
  char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  char month_abbr[4];
  ft_strlcpy(month_abbr, &time[4], 4);
  month_abbr[3] = '\0';

  int month_num;
  for (month_num = 0; month_num < 12; month_num++)
    if (ft_strncmp(months[month_num], month_abbr, 3) == 0)
      break;

  if (month_num < 9) {
    month_str[0] = '0';
    month_str[1] = '1' + month_num;
  } else {
    month_str[0] = '1';
    month_str[1] = '0' + month_num - 9;
  }
  month_str[2] = '\0';

  ft_strlcpy(day_str, &time[8], 3);
  day_str[2] = '\0';

  if (day_str[0] == ' ')
    day_str[0] = '0';
}

void write_iso(const char *month_str, const char *day_str, const char *time) {
  write(1, month_str, 2);
  write(1, "-", 1);
  write(1, day_str, 2);
  write(1, " ", 1);
  write(1, &time[11], 5);
}

void write_long_iso(const char *time, const char *month_str,
                    const char *day_str) {
  write(1, &time[20], 4);
  write(1, "-", 1);
  write(1, month_str, 2);
  write(1, "-", 1);
  write(1, day_str, 2);
  write(1, " ", 1);
  write(1, &time[11], 5);
}

void write_full_iso(struct stat fileStat, char *time, char *month_str,
                    char *day_str) {

  struct timespec ts;
#ifdef __APPLE__
  ts = fileStat.st_mtimespec;
#else
  ts = fileStat.st_mtim;
#endif

  struct tm *tm;
  tm = localtime(&ts.tv_sec);

  char nano_str[10] = ".000000000";
  for (int i = 9; i >= 1; i--) {
    nano_str[i] = '0' + ts.tv_nsec % 10;
    ts.tv_nsec /= 10;
  }

  int offset = tm->tm_gmtoff;             // timezone offset in seconds
  int abs_offset = abs(offset);           // absolute value of the offset
  int hours = abs_offset / 3600;          // convert to hours
  int minutes = (abs_offset % 3600) / 60; // convert the remainder to minutes

  char tz_str[6] = "+0000";
  for (int i = 3; i >= 2; i--) {
    tz_str[i] = '0' + minutes % 10;
    minutes /= 10;
  }
  for (int i = 2; i >= 1; i--) {
    tz_str[i] = '0' + hours % 10;
    hours /= 10;
  }
  if (offset < 0)
    tz_str[0] = '-';

  write(1, &time[20], 4);
  write(1, "-", 1);
  write(1, month_str, 2);
  write(1, "-", 1);
  write(1, day_str, 2);
  write(1, " ", 1);
  write(1, &time[10], 9);
  write(1, nano_str, 10);
  write(1, " ", 1);
  write(1, tz_str, 5);
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

void print_symbolic_link_target(struct dirent *entry, struct stat fileStat) {
  if (S_ISLNK(fileStat.st_mode)) {
    char link_target[1024];
    ssize_t len = readlink(entry->d_name, link_target, sizeof(link_target) - 1);
    if (len != -1) {
      link_target[len] = '\0';
      write(1, " -> ", 4);
      write(1, link_target, ft_strlen(link_target));
    }
  }
}