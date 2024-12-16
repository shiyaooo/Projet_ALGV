#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "experimentale.h"
#include <ctype.h>  
#include <stdbool.h>
#include <unistd.h>
//  gcc -Wall -o main main.c experimentale.c

int main() {
    Words* lwords=read_Files_Shakespeare("../../Shakespeare");
    printf("\n");
    eciture_words(lwords);
    printf("Successful!\n");
    return 0;
}