#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* O - Opcode,
	R - Register
	S - Symbol
	L - Direct Addressing
	DB - comes with value, hence token: type - DB, value - value with DB token
	DW
	DD
*/
enum TOKEN_TYPES {
	O, R, S, L, DB, DW, DD
} TOKEN_TYPES;

typedef struct token {
	int type;
	int value; // value in decimal
} second_pass_token;

typedef struct l {
	int len;
	second_pass_token *tokens;
} line;

void print_line(line line) {
	for(int i = 0; i < line.len; i++) {
		printf("%d %d\n", line.tokens[i].type, line.tokens[i].value);
	}
	printf("\n");
}

int begins_with(const char *s, const char c) {
	if (s[0] == c)
		return 1;
	return 0;
}

char *strip_newline(char *s) {
	if(s[strlen(s) - 1] == '\n')
		s[strlen(s) - 1] = '\0';
	return s;
}

int hex_to_dec(char *hex) {
	int len = strlen(hex);
	int base = 1;

	int dec = 0;

	for(int i = len - 1; i >= 0; i--) {
		if(hex[i] >= '0' && hex[i] <= '9') {
			dec += (hex[i] - 48) * base;
			base *= 16;
		} else if(hex[i] >= 'A' && hex[i] <= 'F') {
			dec += (hex[i] - 55) * base;
			base *= 16;
		}
	}

	return dec;
}

char* substr(const char *src, int m, int n)
{
    int len = n - m;
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
    strncpy(dest, (src + m), len);
    return dest;
}

second_pass_token make_token(char *str) {
	second_pass_token t;
	t.type = 0; t.value = 0;

	if (begins_with(str, 'O')) {
		t.type = O;
		t.value = atoi(substr(str, 1, strlen(str)));
	} else if (begins_with(str, 'R')) {
		t.type = R;
		t.value = atoi(substr(str, 1, strlen(str)));
	} else if (begins_with(str, 'S')) {
		t.type = S;
		int val = hex_to_dec(substr(str, 1, strlen(str))); // ? query about value following S, is it a decimal or hex value 
		if(val < 0 || val > 99) {
			fprintf(stderr, "Symbol value range [00 - 99]\n");
			exit(EXIT_FAILURE);
		} else {
			t.value = val;
		}
	} else if (begins_with(str, 'L')) {
		t.type = L;
		int val = hex_to_dec(substr(str, 1, strlen(str)));
		if (val < 0 || val > 65535) {
			fprintf(stderr, "Direct addressing value range [0000 - FFFF]\n");
			exit(EXIT_FAILURE);
		} else {
			t.value = val;
		}
	} else {
		char *start = substr(str, 0, 2);
		if(strcmp(start,"DB") == 0) {
			t.type = DB; t.value = atoi(substr(str, 2, strlen(str)));
		} else if(strcmp(start,"DW") == 0) {
			t.type = DW; t.value = atoi(substr(str, 2, strlen(str)));
		} else if(strcmp(start,"DD") == 0) {
			t.type = DD; t.value = atoi(substr(str, 2, strlen(str)));
		} else {
			fprintf(stderr, "Invalid token\n");
			exit(EXIT_FAILURE);
		}
	}
		
	return t;
}

/*
 * Replace main in second_pass_parse.c with this function
 * args : const char *filename
 * returns: line (all tokens for the file, not line wise)
 */
line parse_intermediate_file(const char *filename);
