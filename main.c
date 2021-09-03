#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define NELEMS(x) (sizeof(x) / sizeof((x)[0]))
#define null NULL

// https://jsbin.com/tamuculebi/1/edit?js,console

#define copyright_info\
    "Copyright (c) Robin White.\n" \
    "License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.\n" \
    "This is free software: you are free to change and redistribute it.\n" \
    "There is NO WARRANTY, to the extent permitted by law.\n" \
    "\nWritten by Robin White\n"

static int handle_args(int argc, char* argv[])
{
    for(int i= 0; i<argc; i++) {
	if (argv[i][0] == '-') {
	    if (argv[i][1] == 'v') {
		#ifdef build
		printf("%s %s\n%s\nBuilt on: %s\nBuilt at: %s\n",
		       target, version, copyright_info, build, time);
		#endif
		exit(0);
	    }
	    if (argv[i][1] == 'h') {
		puts("Usage test [OPTION]... [FILE]...");
		puts("Options:");
		puts("  -h      display this information");
		puts("  -v      display version information");
		exit(0);
	    }
	}
    }
    return 0;
}
/**
 * o: offset:    number of positions backwards to find start of matching string
 * l: length:    length of the match
 * c: character: character found *after* the match
 */
typedef struct {
    int o;
    int l;
    char c;
} Triple;

Triple* new_triple(int o, int l, char c)
{
    Triple* t = (Triple*)malloc(sizeof(Triple));
    t->o = o;
    t->l = l;
    t->c = c;
    return t;
}

void print_triple(Triple* t)
{
    printf("{%d, %d, %c}\n", t->o, t->l, t->c);
}

void print_array(uint8_t* array, size_t size, bool new_line)
{
    for (int i=0; i<size; i++) {
	printf("%c", array[i]);
    }
    if (new_line) printf("\n");
}

void print_status(int count, int l, uint8_t *search_buffer, uint8_t *ahead_buffer)
{
    printf("[%-2d]: ", count);
    for (int i=0; i<count; i++) {
	printf("%c", search_buffer[i]);
    }
    printf("[%c]", ahead_buffer[count]);
    for (int i=0; i<l-1; i++) {
	printf("%c", ahead_buffer[i+1]);
    }
    printf("\n");
}

static size_t rsearch(uint8_t* p, size_t p_len, uint8_t* a, size_t a_len)
{
    for (size_t i=a_len; i>0; i--) {
	bool equal = memcmp(a+i, p, p_len) == 0;
	if (equal) return i;
    }
    return -1;
}

int main(int argc, char** argv)
{
    handle_args(argc, argv);
    
    uint8_t str[] = {97, 98, 97, 98, 99, 98, 97, 98, 97, 98, 97, 97};
    uint64_t length = NELEMS(str);
    uint8_t search_buffer[length];
    uint8_t* ahead_buffer = &str[0];

    print_array(str, length, true);
    
    for (int i=0; i<length; i++ ) {
	print_status(i, length-i, search_buffer, ahead_buffer);
	bool found = false;
	for (int j=0; j<length-i; j++) {
	    uint8_t result = rsearch(ahead_buffer+i, length-j-i, search_buffer, i);
	    printf("searching ");
	    print_array(search_buffer, i, false);
	    printf(" for ");
	    print_array(ahead_buffer+i, length-j-i, false);
	    printf(" should be %ld long\n", length-j-i);
	    
	    
	    //printf("index of search: %d\n", result);
	}
	search_buffer[i] = ahead_buffer[i];
	getchar();
    }

    printf("%s\n", str);

    uint8_t baa[] = {98,97,97};
    size_t pos = rsearch(baa, 3, str, length);

    printf("should be 9: %ld\n", pos);
    
    return 0;
}
