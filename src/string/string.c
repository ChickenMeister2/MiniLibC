// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	if (destination == NULL) {
		return NULL;
	}
	char *ptr = destination;
	while (*source != '\0') {
		*destination = *source;
		destination++;
		source++;
	}

	*destination = '\0';
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	size_t i;

	for (i = 0; i < len && source[i] != '\0'; i++)
		destination[i] = source[i];
	for ( ; i < len; i++)
		destination[i] = '\0';
	
	return destination;
}

char *strcat(char *destination, const char *source)
{
	char* ptr = destination + strlen(destination);

	// appends characters of the source to the destination string
	while (*source != '\0') {
		*ptr++ = *source++;
	}

	// null terminate destination string
	*ptr = '\0';

	// the destination is returned by standard `strcat()`
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	size_t dest_len = strlen(destination);
	size_t i;

	for (i = 0 ; i < len && source[i] != '\0' ; i++)
		destination[dest_len + i] = source[i];
	destination[dest_len + i] = '\0';

	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	while(*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	while ( len && *str1 && ( *str1 == *str2 ) ) {
		++str1;
		++str2;
		--len;
	}
	if ( len == 0 ) {
		return 0;
	} else {
		return ( *(unsigned char *)str1 - *(unsigned char *)str2 );
	}
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	char ch;

	ch = c;
	for (;; ++str) {
		if (*str == c)
			return ((char *)str);
		if (*str == '\0')
			return (NULL);
	}
}

char *strrchr(const char *str, int c)
{
	char *save;
	char ch;

	ch = c;
	for (save = NULL;; ++str) {
		if (*str == ch)
			save = (char *)str;
		if (*str == '\0')
			return (save);
	}
}

char *strstr(const char *haystack, const char *needle)
{
	if (*needle == '\0')
		return (char *)haystack;

	for (const char *h = haystack; *h != '\0'; h++)
	{
		if (*h != *needle)
			continue;

		const char *hp = h;
		const char *np = needle;
		for ( ; *hp != '\0' && *np != '\0'; hp++, np++)
		{
			if (*hp != *np)
				break;
		}

		if (*np == '\0')
			return (char *)h;
	}
	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	if (*needle == '\0')
		return (char *)haystack;

	char *result = NULL;
	for (char *p = strstr(haystack, needle); p != NULL; p = strstr(p + 1, needle))
	{
		result = p;
	}

	return result;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	char *dest = (char *)destination;
	const char *src = (const char *)source;

	for (size_t i = 0; i < num; i++)
		dest[i] = src[i];

	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	char *dest = (char *)destination;
	const char *src = (const char *)source;

	if (dest <= src)
	{
		for (size_t i = 0; i < num; i++)
			dest[i] = src[i];
	}
	else
	{
		for (size_t i = num; i > 0; i--)
			dest[i-1] = src[i-1];
	}

	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	
	unsigned char u1, u2;

	for ( ; num-- ; ptr1++, ptr2++) {
		u1 = * (unsigned char *) ptr1;
		u2 = * (unsigned char *) ptr2;
		if ( u1 != u2) {
			return (u1-u2);
		}	
	}
	
	return 0;
}

void *memset(void *source, int value, size_t num)
{
	unsigned char *src = (unsigned char *)source;

	for (size_t i = 0; i < num; i++)
		src[i] = (unsigned char)value;

	return source;
}
