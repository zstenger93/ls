# 📖 ft_ls

## 🗣️ About

The goal is to recode a smaller version of the ls command

### Handled flags:

`-l` Long listing format

`-a` Show hidden files starting with .

`-r` Reverse the order of the list

`-t` Order the list by the last modification date

`-R` List everything recursively

`-p` Show / after folders

`-h` Human readable display for size

`-S` Order by file size

`-n` Display gid and uid as IDs

`-o` Do not display owner

`-g` Do not Display group

`-x` List entries by lines

It can take flags one by one as `-l -a` for example or `-la`

Also can pass one or more folders in argument for example `./ft_ls src -laR includes`

Colorized output for permissions and file/folders

`--help` for basic information

`--time-style=` for different time outputs with `iso`, `full-iso` and `long-iso`