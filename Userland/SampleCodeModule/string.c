#include <string.h>
#include <stdint.h>

void _strcpy(char * dest, char * src, int n){
    while (*src != '\0' && n > 0){
        *dest++ = *src++;
        n--;
    }
    *dest = '\0';
}

uint64_t _strlen(const char * str){
	uint64_t ans = 0;
    while(*str != '\0'){
        ans++;
        str++;
    }
	return ans;
}

int _strcmp(char *str1, char *str2){
	while( ( *str1 != '\0' && *str2 != '\0' ) && *str1 == *str2 )
    {
        str1++;
        str2++;
    }

    if(*str1 == *str2)
    {
        return 0; // strings are identical
    }

    else
    {
        return *str1 - *str2;
    }
}