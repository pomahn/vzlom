
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

enum 
{
    _ACCESS_DENIED = 1
};

void root_access(void)
{
    puts("root granted");
}

void access_denied(void)
{
    puts("Fail");
    exit(_ACCESS_DENIED);
}

void stage1(void)
{
    static const char* passwd = "Jenya, gde la6bI\n";
    
    char buffer[50] = {};
    if (strcmp(fgets(buffer, 50, stdin), passwd) == 0)
        root_access();
    else
        access_denied();
}

unsigned int hash(const char* str)
{
    unsigned int hash = 0;
    while (*str)
    {
        hash += (*str);
        str++;
    }

    return hash;
}

void stage2(void)
{
    // password is "Pohoje vse ploxo\n"
    static const unsigned int PHASE2_HASH = 1583;
    
    char buffer[50] = {};
    if (hash(fgets(buffer, 50, stdin)) == PHASE2_HASH)
        root_access();
    else
        access_denied();
}

unsigned rot13(const char * str) 
{
	unsigned hash = 0;

	for(; *str; str++)
	{
		hash += (unsigned char)(*str);
		hash -= (hash << 13) | (hash >> 19);
	}

	return hash;

}

int check_password_stage3(const char* str)
{
    // password is "Jene popa\n"
    static const int PHASE3_HASH = -45361123;

    return rot13(str) == PHASE3_HASH;
}

void stage3(void)
{
    char buffer[50] = {};
    if (check_password_stage3(buffer))
        root_access();
    else
        access_denied();
}

int main()
{
    puts("first check");
    stage1();
    puts("OK, second"); 
    stage2();
    puts("last one");
    stage3();
    puts("You win");
    
    return 0;
}



