#include <stdio.h>
#include <string.h>
#include "strlib.h"

int main() {
    // Test for str_charAt
    char *testStr = "Hello, World!";
    printf("charAt(7) of \"%s\": %c (forventet: W)\n", testStr, str_charAt(testStr, 7));

    // Test for str_concat
    char result[50]; // Buffer for the result
    str_concat("Hello, ", "World!", result);
    printf("concat(\"Hello, \", \"World!\"): %s (forventet: Hello, World!)\n", result);

    // Test for str_includes
    printf("includes(\"World\") in \"%s\": %d (forventet: 1)\n", testStr, str_includes(testStr, "World"));
    printf("includes(\"Earth\") in \"%s\": %d (forventet: 0)\n", testStr, str_includes(testStr, "Earth"));

    // Test for str_indexOf
    printf("indexOf(\"World\") in \"%s\": %d (forventet: 7)\n", testStr, str_indexOf(testStr, "World"));
    printf("indexOf(\"Earth\") in \"%s\": %d (forventet: -1)\n", testStr, str_indexOf(testStr, "Earth"));

    // Test for str_startsWith
    printf("startsWith(\"Hello\") in \"%s\": %d (forventet: 1)\n", testStr, str_startsWith(testStr, "Hello"));
    printf("startsWith(\"World\") in \"%s\": %d (forventet: 0)\n", testStr, str_startsWith(testStr, "World"));

    // Test for str_endsWith
    printf("endsWith(\"World!\") in \"%s\": %d (forventet: 1)\n", testStr, str_endsWith(testStr, "World!"));
    printf("endsWith(\"Hello\") in \"%s\": %d (forventet: 0)\n", testStr, str_endsWith(testStr, "Hello"));

    // Test for str_toLowerCase
    char lowerStr[] = "HELLO WORLD!";
    str_toLowerCase(lowerStr);
    printf("toLowerCase(\"HELLO WORLD!\"): %s (forventet: hello world!)\n", lowerStr);

    // Test for str_toUpperCase
    char upperStr[] = "hello world!";
    str_toUpperCase(upperStr);
    printf("toUpperCase(\"hello world!\"): %s (forventet: HELLO WORLD!)\n", upperStr);

    // Test for str_localeCompare
    printf("localeCompare(\"Hello\", \"Hello\"): %d (forventet: 1)\n", str_localeCompare("Hello", "Hello"));
    printf("localeCompare(\"Hello\", \"World\"): %d (forventet: 0)\n", str_localeCompare("Hello", "World"));

    // Test for str_substring
    char substr[] = "Hello, World!";
    str_substring(substr, 7, 12);
    printf("substring(7, 12) of \"Hello, World!\": %s (forventet: World)\n", substr);

    // Test for str_trim
    char trimStr[] = "   Hello, World!   ";
    str_trim(trimStr);
    printf("trim(\"   Hello, World!   \"): \"%s\" (forventet: \"Hello, World!\")\n", trimStr);

    // Test for str_trimStart
    char trimStartStr[] = "   Hello, World!   ";
    str_trimStart(trimStartStr);
    printf("trimStart(\"   Hello, World!   \"): \"%s\" (forventet: \"Hello, World!   \")\n", trimStartStr);

    // Test for str_trimEnd
    char trimEndStr[] = "   Hello, World!   ";
    str_trimEnd(trimEndStr);
    printf("trimEnd(\"   Hello, World!   \"): \"%s\" (forventet: \"   Hello, World!\")\n", trimEndStr);

    // Test for str_length
    printf("length of \"%s\": %zu (forventet: 13)\n", testStr, str_length(testStr));

    return 0;
}
