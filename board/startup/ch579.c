#include "CH57x_common.h"
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

void usb_dc_low_level_init(void)
{
}

void board_init(void)
{
}


__attribute__((weak)) int __io_putchar(int ch)
{
    return ch;
}

__attribute__((weak)) int __io_getchar(void)
{
    return 0;
}

int _write(int fd, char *pBuffer, int size)
{
    extern int __io_putchar(int ch);
    for (int i = 0; i < size; i++) {
        __io_putchar(*pBuffer++);
    }
    return size;
}

__attribute__((weak)) int _read(int file, char *ptr, int len)
{
    (void)file;
    int DataIdx;
    for (DataIdx = 0; DataIdx < len; DataIdx++) {
        *ptr++ = __io_getchar();
    }
    return len;
}

__attribute__((weak)) int _isatty(int fd)
{
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
        return 1;

    errno = EBADF;
    return 0;
}

__attribute__((weak)) int _close(int fd)
{
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
        return 0;

    errno = EBADF;
    return -1;
}

__attribute__((weak)) int _lseek(int fd, int ptr, int dir)
{
    (void)fd;
    (void)ptr;
    (void)dir;

    errno = EBADF;
    return -1;
}

__attribute__((weak)) int _fstat(int fd, struct stat *st)
{
    if (fd >= STDIN_FILENO && fd <= STDERR_FILENO) {
        st->st_mode = S_IFCHR;
        return 0;
    }

    errno = EBADF;
    return 0;
}