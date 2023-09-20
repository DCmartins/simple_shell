#include "shell.h"

/**
 * _eputs - Display an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void _eputs(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
_eputchar(str[i]);
i++;
}
}
/**
 * _eputchar - Write the character 'c' to stderr.
 * @c: The character to print.
 *
 * Return: 1 on success, -1 on error with errno set accordingly.
 */
int _eputchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(2, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}
/**
 * _putfd - Write the char 'c' to the specified file descriptor 'fd'.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: 1 on success, -1 on error with errno set accordingly.
 */
int _putfd(char c, int fd)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(fd, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}
/**
 * _putsfd - Print an input string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int _putsfd(char *str, int fd)
{
int i = 0;

if (!str)
return (0);
while (*str)
{
i += _putfd(*str++, fd);
}
return (i);
}
