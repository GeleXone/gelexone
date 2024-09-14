#include "Xone/x_string.h"

//Количество СИМВОЛОВ, без '\0'
unsigned int x_strlen(const char* string) {
	unsigned int i = 0;
	for (; string[i] != '\0'; i++);
	return i;
}

char* x_strcat(char* base_string, const char* other_string) {
	char* ptr = base_string + x_strlen(base_string);
	while (*other_string != '\0') *ptr++ = *other_string++;
	*ptr = '\0';
	return base_string;
}

char* x_straddc(char* base, char c) {
	char* ptr = base + x_strlen(base);
	ptr[0] = c;
	ptr[1] = '\0';
	return base;
}

boolean x_strcmp(char* a, char* b) {
	unsigned int length = x_strlen(a);
	if (length != x_strlen(b))
		return FALSE;
	for (unsigned int i = 0; i < length; i++)
		if (a[i] != b[i])
			return FALSE;
	return TRUE;
}

boolean x_is_substring(const char* sub, char* origin) {
	unsigned int length = x_strlen(sub), k = 0;
	boolean guess = FALSE;
	while (!guess && k < length) {
		if (origin[k] != sub[0])
			k++;
		else
			guess = TRUE;
		for (unsigned int i = 0; i < length; i++)
			if (sub[i] != origin[k + i]) {
				guess = FALSE;
				k++;
			}

	}
	return guess;
}