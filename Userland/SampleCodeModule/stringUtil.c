#include <stringUtil.h>
#include <libVid.h>
#include <stdint.h>

#define isHexa(a) ( (((a) >= '0' && (a) <= '9') || ((a) >= 'a' && (a) <= 'f') || ((a) >= 'A' && (a) <= 'F')) ? 1 : 0 )

int checkMem(char mem[]){
    uint64_t len = _strlen(mem);
    //0x........ -> if it matches ^0x[a-fA-F0-9]{16}
    if (len < 2 || len > 18 || mem[0] != '0' || mem[1] != 'x'){
        return 0;
    }

    for (int i = 2; i < len; i++){
        if (!isHexa(mem[i])){
            return 0;
        }
    }
    return 1;
}

uint64_t hexStrToInt(char* s) {
    int i = 0;
    int len = _strlen(s);
    uint64_t res = 0;

    // check if s begins with 0x
    if(*s == '0' || *(s+1) == 'x') i = 2;

    // error numero mucho grande
    if (len - i > 32) return 0;

    for(; i < len; ++i) {
        if (s[i] >= '0' && s[i] <= '9')
            res = res*16 + (s[i]-'0');
        else 
        if (s[i] >= 'a' && s[i] <= 'f')
            res = res*16 + (s[i]-'a'+10);
        else
        if (s[i] >= 'A' && s[i] <= 'F')
            res = res*16 + (s[i]-'A'+10);
        
    }

    return res;
}

uint64_t atoi(char S[])
{
    uint64_t num = 0;
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
    while(str[ans] != '\0'){
        ans++;
        //str++;
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

