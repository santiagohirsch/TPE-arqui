#include <stringUtil.h>
#include <stdint.h>

long atoi(char S[])
{
    long num = 0;
    int i = 0;
    // run till the end of the string is reached, or the
    // current character is non-numeric
    while (S[i] && (S[i] >= '0' && S[i] <= '9'))
    {
        num = num * 10 + (S[i] - '0');
        i++;
    }
    return num;
}

uint64_t getFormat(uint64_t n) {
	uint64_t dec = n & 240;
	dec = dec >> 4;
	uint64_t units = n & 15;
	return dec * 10 + units;
}

uint64_t itoa(uint64_t number, char* s) {
    int digits = 1;
	for (int n=number/10; n != 0; digits++, n /= 10);

    if(digits == 1) {
        s[0] = '0';
        s[1] = number + '0';
        s[2] = 0;
        return digits;
    }
	
	s[digits] = 0;    
	for (int i=digits-1; i>=0; i--) {
		s[i] = (number % 10) + '0';
		number /= 10;
	}
	
	return digits;
}


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

