#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_ascii(unsigned char byte);
int is_continuation(unsigned char byte);
int str_length(const char *str);
int str_codePointAt(const char *str, int index);
char* str_fromCodePoint(int codePoint);
char* str_substring(const char* str, int firstIndex, int lastIndex);

// Check if byte is ASCII
int is_ascii(unsigned char byte) {
    return byte < 0x80;
}

// Check if byte is a continuation byte (for multi-byte characters)
int is_continuation(unsigned char byte) {
    return (byte & 0xC0) == 0x80; 
}

// Byte checker
int start_of_sequence(unsigned char byte) {
    if (byte < 0x80) return 1; // 1-byte character
    if ((byte & 0xE0) == 0xC0) return 2; // 2-byte character
    if ((byte & 0xF0) == 0xE0) return 3; // 3-byte character
    if ((byte & 0xF8) == 0xF0) return 4; // 4-byte character
    return 0; // Invalid byte
}

// Function to calculate the length of the UTF-8 string
int str_length(const char *str) {
    int length = 0;
    for (int i = 0; str[i] != '\0';) {
        int bytes = start_of_sequence((unsigned char) str[i]);
        if (bytes == 0) {
            break; // Invalid byte handling
        }
        length++;
        i += bytes; // Move the index by the number of bytes in the character
    }
    return length;
}

// Updated str_substring function to handle UTF-8
char* str_substring(const char* str, int firstIndex, int lastIndex) {
    int strLength = str_length(str); // Get length of the UTF-8 string

    // If index limits are invalid, show an error message
    if (firstIndex < 0 || lastIndex > strLength || lastIndex <= firstIndex) {
        printf("Fejl i indekserne\n");
        return NULL; // Return NULL to indicate an error
    }

    // Allocate memory for the new substring
    char *result = (char*) malloc((lastIndex - firstIndex + 1) * sizeof(char)); // +1 for null-terminator
    if (result == NULL) {
        printf("Hukommelsesallokering mislykkedes\n");
        return NULL;
    }

    int codePointIndex = 0; // Counter for code points
    int resultIndex = 0;    // Index for the result string

    for (int i = 0; str[i] != '\0';) {
        int bytes = start_of_sequence((unsigned char) str[i]);
        if (bytes == 0) {
            free(result); // Free allocated memory on error
            return NULL; // Return NULL on invalid byte
        }

        // If the current character index is within the desired range
        if (codePointIndex >= firstIndex && codePointIndex < lastIndex) {
            // Copy the character to the result
            for (int j = 0; j < bytes; j++) {
                result[resultIndex++] = str[i + j];
            }
        }

        if (codePointIndex == lastIndex) {
            break; // Stop copying after lastIndex
        }

        codePointIndex++;
        i += bytes; // Move to the next character
    }

    result[resultIndex] = '\0'; // Null-terminate the result
    return result; // Return the new substring
}

int str_codePointAt(const char *str, int index) {
    int codePointIndex = 0; // Counter for code points
    for (int i = 0; str[i] != '\0';) {
        int bytes = start_of_sequence((unsigned char) str[i]);
        if (bytes == 0) {
            return -1; // Invalid byte handling can be added here
        }

        if (codePointIndex == index) {
            int codePoint = 0;

            // Handle multi-byte code points
            if (bytes == 1) {
                codePoint = str[i]; // Single byte ASCII
            } else {
                // Start with the first byte and mask the relevant bits
                codePoint = str[i] & ((1 << (8 - bytes)) - 1); // Mask leading bits
                for (int j = 1; j < bytes; j++) {
                    codePoint = (codePoint << 6) | (str[i + j] & 0x3F); // Add continuation bytes
                }
            }

            return codePoint; // Return the actual code point
        }

        codePointIndex++;
        i += bytes; // Move the index by the number of bytes in the character
    }
    return -1; // Return -1 if index is out of bounds
}

char* str_fromCodePoint(int codePoint) {
    char *utf8 = (char*) malloc(5); 
    if (codePoint < 0x80) {
        utf8[0] = (char)codePoint;
        utf8[1] = '\0';
    } else if (codePoint < 0x800) {
        utf8[0] = 0xC0 | (codePoint >> 6);
        utf8[1] = 0x80 | (codePoint & 0x3F);
        utf8[2] = '\0';
    } else if (codePoint < 0x10000) {
        utf8[0] = 0xE0 | (codePoint >> 12);
        utf8[1] = 0x80 | ((codePoint >> 6) & 0x3F);
        utf8[2] = 0x80 | (codePoint & 0x3F);
        utf8[3] = '\0';
    } else if (codePoint < 0x110000) {
        utf8[0] = 0xF0 | (codePoint >> 18);
        utf8[1] = 0x80 | ((codePoint >> 12) & 0x3F);
        utf8[2] = 0x80 | ((codePoint >> 6) & 0x3F);
        utf8[3] = 0x80 | (codePoint & 0x3F);
        utf8[4] = '\0';
    }
    return utf8; 
}

int main() {
    const char* testStr = "🍎grød";
    
    printf("Length of str: %d\n", str_length(testStr));

    // Call str_substring and store the result
    char *subStr = str_substring(testStr, 0, 2);
    if (subStr) {
        printf("Substring: %s\n", subStr); // Expected: 🍎g
        free(subStr); // Free the allocated memory
    } else {
        printf("Kunne ikke oprette substring.\n");
    }

    printf("Code point at index 0: %d\n", str_codePointAt(testStr, 0)); 
    printf("Code point at index 1: %d\n", str_codePointAt(testStr, 1)); 
    printf("Code point at index 2: %d\n", str_codePointAt(testStr, 2)); 
    printf("Code point at index 3: %d\n", str_codePointAt(testStr, 3)); 
    printf("Code point at index 4: %d\n", str_codePointAt(testStr, 4)); 

    char *newStr = str_fromCodePoint(0x1F34E);
    printf("UTF-8 string from code point: %s\n", newStr); // Expected: 🍎
    
    free(newStr);
    return 0;
}
