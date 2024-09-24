#include <stdio.h>
#include "strlib.h"
#include <string.h>
#include <ctype.h> // til tolower() og toupper()

// Returnerer tegnet ved det angivne indeks
char str_charAt(const char *str, size_t index) {
    if (index >= strlen(str)) {
        return '\0'; // Hvis indeks er uden for strenglængden, returner '\0' (tom karakter)
    }
    return str[index]; // Returner tegnet ved det angivne indeks
}

// Sammenkæder to strenge og gemmer resultatet i output-bufferen
void str_concat(const char *str1, const char *str2, char *output) {
    while (*str1) { // Kopier str1 til output
        *output++ = *str1++;
    }
    while (*str2) { // Kopier str2 til output efter str1
        *output++ = *str2++;
    }
    *output = '\0'; // Tilføj null-terminator for at markere slutningen af strengen
}

// Tjekker, om en streng indeholder en substring
int str_includes(const char *str, const char *substr) {
    return strstr(str, substr) != NULL; // Returner 1 (true), hvis substr findes i str, ellers 0 (false)
}

// Returnerer indekset for den første forekomst af en given understreng, eller -1 hvis den ikke findes
int str_indexOf(const char *str, const char *substr) {
    char *pos = strstr(str, substr); // Find positionen af substr i str
    if (pos) {
        return pos - str; // Beregn og returner indekset
    }
    return -1; // Returner -1 hvis understrengen ikke findes
}

// Tjekker, om strengen starter med den substringen
int str_startsWith(const char *str, const char *substr) {
    while (*substr) { // Gennemgå begge strenge
        if (*str++ != *substr++) {
            return 0; // Returner 0 (false), hvis de ikke matcher
        }
    }
    return 1; // Returner 1 (true), hvis strengen starter med substr
}

// Tjekker, om strengen slutter med den angivne understreng
int str_endsWith(const char *str, const char *substr) {
    size_t str_len = strlen(str);
    size_t substr_len = strlen(substr);
    if (substr_len > str_len) return 0; // Hvis substr er længere end str, returner 0 (false)

    return strcmp(str + str_len - substr_len, substr) == 0; // Sammenlign slutningen af strengen med substr
}

// Konverterer alle tegn i strengen til lowercase
void str_toLowerCase(char *str) {
    while (*str) {
        *str = tolower(*str); // Konverter hvert tegn til lowercase
        str++;
    }
}

// Konverterer alle tegn i strengen til uppercase
void str_toUpperCase(char *str) {
    while (*str) {
        *str = toupper(*str); // Konverter hvert tegn til uppercase
        str++;
    }
}

// Sammenligner to strenge og returnerer 1 hvis de er ens, ellers 0
int str_localeCompare(char* firstStr, char* secondStr) {
    int firstStrLength = 0;
    int secondStrLength = 0;

    // Beregn længden af firstStr
    while (*firstStr) {
        firstStrLength++;
        firstStr++;
    }

    // Beregn længden af secondStr
    while (*secondStr) {
        secondStrLength++;
        secondStr++;
    }
    
    if (firstStrLength != secondStrLength) {
        return 0; // Hvis længderne er forskellige, er strengene ikke ens
    }

    // Sæt pointerne tilbage til starten af strengene
    firstStr -= firstStrLength;
    secondStr -= secondStrLength;

    // Sammenlign hvert tegn i strengene
    while (*firstStr) {
        if (*firstStr != *secondStr) {
            return 0; // Hvis der er en forskel, returner 0
        }
        firstStr++;
        secondStr++;
    }

    return 1; // Hvis alle tegn matcher, returner 1
}

// Ekstraherer en del af strengen mellem to indekser og gemmer den i samme streng
void str_substring(char* str, int firstIndex, int lastIndex) {
    int strLength = 0;
    char *strCpy = str; // Lav en kopi af str

    // Beregn længden af strengen
    while (*str) {
        strLength++;
        str++;
    }

    // Sæt str-pointeren tilbage til starten
    str = strCpy;

    // Hvis indeksgrænserne er ugyldige, vis en fejlmeddelelse
    if (firstIndex < 0 || lastIndex > strLength || lastIndex <= firstIndex) {
        printf("Fejl i indekserne\n");
        return;
    }

    // Kopier tegnene fra firstIndex til lastIndex til den oprindelige streng
    for (int i = firstIndex; i < lastIndex; i++) {
        *str++ = *(strCpy + i);
    }
    
    *str = '\0'; // Tilføj null-terminator for at markere slutningen af den nye streng
}

// Fjerner mellemrum fra både starten og slutningen af en streng
void str_trim(char *str) {
    str_trimStart(str); // Fjern mellemrum fra starten
    str_trimEnd(str);   // Fjern mellemrum fra slutningen
}

// Fjerner mellemrum fra starten af en streng
void str_trimStart(char *str) {
    char *start = str;
    while (isspace(*start)) start++; // Find første tegn, der ikke er et mellemrum
    memmove(str, start, strlen(start) + 1); // Flyt den trimmede streng til starten
}

// Fjerner mellemrum fra slutningen af en streng
void str_trimEnd(char *str) {
    char *end = str + strlen(str) - 1;
    while (end >= str && isspace(*end)) end--; // Find sidste tegn, der ikke er et mellemrum
    *(end + 1) = '\0'; // Tilføj null-terminator efter sidste tegn
}

// Returnerer længden af en streng
size_t str_length(const char *str) {
    return strlen(str); // Brug strlen til at returnere længden af strengen
}
