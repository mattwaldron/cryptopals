#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "conversions.h"

int main (int argv, char ** argc) {
    char in [] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    char * out;

    printf("Input: %s\n", in);

    hex_b64_translate(in, &out, strlen(in));

    printf("Output: %s\n", out);
    return 0;
}

// matt@mattpc:~/cryptopals$ gcc --std=c99 s1c1.c
// matt@mattpc:~/cryptopals$ ./a.out
// Input: 49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
// Output: SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t
