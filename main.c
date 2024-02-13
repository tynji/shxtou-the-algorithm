#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define
char* strndup_custom(const char* input, size_t n) {
    size_t len = strlen(input);
    size_t copyLen = (len < n) ? len : n;

    char* result = (char*)malloc(copyLen + 1);
    if (result != NULL) {
        memcpy(result, input, copyLen);
        result[copyLen] = '\0';
    }

    return result;
}

// text to base A function; decimal here acts as a medium for conversion
char* convertToBaseA(const char* input, int A) {
    int len = strlen(input);
    long long decimalValue = 0;

    // Convert input text to decimal value
    for (int i = 0; i < len; i++) {
        decimalValue = decimalValue * 256 + input[i];
    }
  
    char baseA[100];
    int index = 0;
  
    while (decimalValue > 0) {
        baseA[index++] = (char)(decimalValue % A);
        decimalValue /= A;
    }

    // result storage
    char* result = (char*)malloc((index + 1) * sizeof(char));
    result[index] = '\0';

    for (int i = index - 1; i >= 0; i--) {
        result[index - 1 - i] = baseA[i] < 10 ? baseA[i] + '0' : baseA[i] - 10 + 'A';
    }

    return result;
}

// silly divide function check
char* checkMax(const char* input, int grSize) {
    int len = strlen(input);
    int remainder = len % grSize;

    if (remainder != 0) {
        // add zero thingy
        char* adjustedInput = (char*)malloc((len + grSize - remainder + 1) * sizeof(char));
        adjustedInput[len + grSize - remainder] = '\0';

        for (int i = 0; i < grSize - remainder; i++) {
            adjustedInput[i] = '0';
        }

        strcpy(adjustedInput + grSize - remainder, input);

        return adjustedInput;
    } else {
        // no adjustment needed
        return strndup_custom(input, len);
    }
}

// the actual dividing
void splitIntoGroups(const char* input, int grSize) {
    int len = strlen(input);
    int numGroups = len / grSize;

    printf("Output in groups of %d characters: ", grSize);
    for (int i = 0; i < numGroups; i++) {
        for (int j = 0; j < grSize; j++) {
            printf("%c", input[i * grSize + j]);
        }
        printf(" ");
    }
    printf("\n");
}

int main() {
    // the rest of this is user input stuff 
    printf("Enter the text: ");
    char inputText[100];
    fgets(inputText, sizeof(inputText), stdin);
    inputText[strcspn(inputText, "\n")] = '\0'; // Remove newline character

    printf("Enter the base A: ");
    int baseA;
    scanf("%d", &baseA);

    // this bit validates user input for base A 
    if (baseA <= 1) {
        printf("Base A should be greater than 1.\n");
        return 1; // Exit with an error code
    }

    // magic shit fuck knows
    char* convertedText = convertToBaseA(inputText, baseA);

    printf("Enter the group size: ");
    int groupSize;
    scanf("%d", &groupSize);

    // Check and adjust length for splitting into groups
    char* adjustedText = checkMax(convertedText, groupSize);

    // Perform splitting
    splitIntoGroups(adjustedText, groupSize);

    // Free allocated memory
    free(convertedText);
    free(adjustedText);

    return 0;
}
