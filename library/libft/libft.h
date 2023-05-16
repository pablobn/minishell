/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:33:51 by pbengoec          #+#    #+#             */
/*   Updated: 2023/04/27 19:29:46 by pbengoec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
// The isalnum() function returns zero if the character tests false and
//      returns non-zero if the character tests true.
int		ft_isalnum(int c);
// If is digit or is alpha == 1 else == 0
int		ft_isalpha(int c);
// The isascii() function tests for an ASCII character, which is any charac-
//      ter between 0 and octal 0177 inclusive.
int		ft_isascii(int c);
// The isdigit() function tests for a decimal digit character.  Regardless
//      of locale, this includes the following characters only:
int		ft_isdigit(int c);
// If character is digit == 1 else == 0
int		ft_isprint(int c);
// The functions strchr() and strrchr() return a pointer to the located
//      character, or NULL if the character does not appear in the string.
char	*ft_strchr(const char *s, int c);
// The functions strchr() and strrchr() return a pointer to the located
//      character, or NULL if the character does not appear in the string.
char	*ft_strrchr(const char *s, int c);
// return length of string
size_t	ft_strlen(const char *s);
// Changes upper-case letter to lower-case letter
int		ft_tolower(int c);
// Changes lower-case letter to upper-case letter
int		ft_toupper(int c);
// Functions return an integer greater than,
//      equal to, or less than 0, according as the string s1 is greater than,
//      equal to, or less than the string s2.  The comparison is done using
//      unsigned characters, so that `\200' is greater than `\0'.
int		ft_strncmp(const char *s1, const char *s2, size_t n);
// The memset() function writes len bytes of value c (converted to an
//      unsigned char) to the string b.
void	*ft_memset(void *b, int c, size_t len);
// The bzero() function writes n zeroed bytes to the string s.  If n is
//      zero, bzero() does nothing.
void	ft_bzero(void *s, size_t n);
// The memcpy() function copies n bytes from memory area src to memory area
//      dst.  If dst and src overlap, behavior is undefined.  Applications in
//      which dst and src might overlap should use memmove(3) instead.
void	*ft_memcpy(void *dst, const void *src, size_t n);
// The memmove() function copies len bytes from string src to string dst.
//      The two strings may overlap; the copy is always done in a 
//      non-destructive manner.
void	*ft_memmove(void *dst, const void *src, size_t len);
// Copy the string src into dst
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
// Appends string src to the end of dst
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
// function locates the first occurrence of c (converted to an
//      unsigned char) in string s.
void	*ft_memchr(const void *s, int c, size_t n);
// The memcmp() function compares byte string s1 against byte string s2.
//      Both strings are assumed to be n bytes long.
int		ft_memcmp(const void *s1, const void *s2, size_t n);
// Find the position of the string where coincide with the string or word given.
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
// Converts string to int;
int		ft_atoi(const char *str);
// Allocate memory to hold an array of 'count', 
// and each 'count' occupies 'size' bytes.
void	*ft_calloc(size_t count, size_t size);
// Copy the memory and value of the string given
// into another new memory with the same value
char	*ft_strdup(const char *s1);
// Trim the string according to the given parameters.
char	*ft_substr(char const *s, unsigned int start, size_t len);
// Append s2 to the end of s1
char	*ft_strjoin(char const *s1, char const *s2);
// Cut the start and the end of the string in case that 
// coincide with any character of the string set
char	*ft_strtrim(char const *s1, char const *set);
// Convert an string to an array of strings 
// with the char c as delimiter
char	**ft_split(char const *s, char c);
// Convert int to string
char	*ft_itoa(int n);
// To each character of the string 's', apply the
// function 'f' giving as parameters the index of each
// character inside 's' and the character itself. Generate
// a new string with the result of successive use
// of 'f'
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
// To each character of the string 's', apply the function
// 'f' giving as parameters the index of each
// character inside 's' and the address of the itself
// character, which can be modified if necessary.
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
// Send character 'c' to file descriptor
// specified.
void	ft_putchar_fd(char c, int fd);
// Send the string 's' to the file descriptor
// specified.
void	ft_putstr_fd(char *s, int fd);
// Send the string 's' to the given file descriptor,
// followed by a line break.
void	ft_putendl_fd(char *s, int fd);
// Send the number 'n' to the given file descriptor.
void	ft_putnbr_fd(int n, int fd);
#endif