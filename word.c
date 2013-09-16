#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG_MODE
#define COUNT 11 
#define WORD_MAX 10

enum {
    RIGHT_WORD = 0,
    WRONG_WORD,
    UNKNOWN_WORD,
};

typedef struct word_rec {
    int jaum;
    int moum;
}WORD_REC;

int insert(char *c)
{
    if(*(c - 1) == '1') {
	*c = '2';
	return 1;
    } else if (*(c - 1) == '2') {
	*c = '1';
	return 1;
    } else if (*(c + 1) == '1') {
	*c = '2';
	return 1;
    } else if (*(c + 1) == '2') {
	*c = '1';
	return 1;
    }

    return 0;
}

int main(void)
{
    int loop = 0;
    int i;
    char *org_word;
    char* input[COUNT] = {"?", "12", "11", "22", "?1??2???1",  "???", "1?2", "??1", "1??1", "1???1", "1??????12?"};

    char* inputs[COUNT];
    for(i = 0; i < COUNT; i++) {
	inputs[i] = (char *)malloc(WORD_MAX);
	strcpy(inputs[i], input[i]);
    }
    org_word = (char*)malloc(WORD_MAX);

    while (loop < COUNT) {
	int sub_loop = 0;
	int result = RIGHT_WORD;
	int str_len = strlen(inputs[loop]);
	char *result_str = NULL;
	WORD_REC wr;

	wr.jaum = 0;
	wr.moum = 0;

	memset(org_word, 0x0, WORD_MAX);
	strcpy(org_word, inputs[loop]);

	if(str_len == 1) {
	    result = RIGHT_WORD;
	} else {
	    while(sub_loop < str_len) {
		char *current = &inputs[loop][sub_loop];

		if(*current == '1') {
		    if(++wr.jaum >= 2) {
			result = WRONG_WORD;
			break;
		    } else {
			wr.moum = 0;
		    } 
		} else if (*current == '2') {
		    if(++wr.moum >= 2) {
			result = WRONG_WORD;
			break;
		    } else {
			wr.jaum = 0;
		    }
		} else if (*current == '?') {
		    wr.moum = 0;
		    wr.jaum = 0;

		    result = UNKNOWN_WORD;

#ifdef DEBUG_MODE
		    printf("index: %d, current: %c --> ", sub_loop, *current);
#endif
		    if(insert(current)) {
#ifdef DEBUG_MODE
			printf("%c\n", *current);
#endif
			sub_loop = 0;
			continue;
		    }
#ifdef DEBUG_MODE
		    printf("cannot insert\n");
#endif
		    sub_loop++;
		    continue;
		} 

#ifdef DEBUG_MODE
		printf("index: %d, current: %c\n", sub_loop, *current);
#endif

		sub_loop++;
	    }
	}

	if(result == WRONG_WORD) {
	    result_str = "wrong word";
	} else if(result == RIGHT_WORD) {
	    result_str = "right word";
	} else {
	    result_str = "unknown word";
	}

#ifdef DEBUG_MODE
	printf("%s (%s) : %s\n", org_word, inputs[loop], result_str);
#else
	printf("%s : %s\n", org_word, result_str);
#endif

	loop++;
    }

    free(org_word);
    for(i = 0; i < COUNT; i++) {
	free(inputs[i]);
    }

    return 0;
}
