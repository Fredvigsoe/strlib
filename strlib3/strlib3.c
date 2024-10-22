#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct {
    char *data; // Pointer til starten af den UTF-8 encodede streng
    size_t length; // Længden af strengen i bytes
    bool owns_data; // Angiver om vi ejer hukommelsen og skal frigive den
} String;

// Opretter en ny String struct som peger på den angivne UTF-8 streng
String str_construct(char *str) {
    String new_string;
    new_string.data = str;
    new_string.length = strlen(str);
    new_string.owns_data = false;  // Ejer ikke strengen
    return new_string;
}

// Returnerer en NUL-termineret UTF-8 streng fra String struct
char* str_valueOf(String string, bool *is_allocated) {
    *is_allocated = false; // Standard: Ingen hukommelse allokeret

    // Hvis den eksisterende streng allerede er NUL-termineret
    if (string.data[string.length] == '\0') {
        return string.data; // Returnér den originale streng
    }

    // Alloker en ny streng og kopier indholdet
    char *null_terminated_string = (char*) malloc((string.length + 1) * sizeof(char));
    if (null_terminated_string == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    strncpy(null_terminated_string, string.data, string.length);
    null_terminated_string[string.length] = '\0'; // Tilføj NUL-terminator

    *is_allocated = true; // Angiver at der er allokeret hukommelse
    return null_terminated_string;
}

// Frigiver hukommelsen brugt af strengen, hvis den var allokeret
void str_destruct(String string) {
    if (string.owns_data && string.data) {
        free(string.data);  // Kun frigør hvis vi ejer strengen
    }
}

// Returnerer en substring fra start til end (uden at kopiere)
String str_substring(String string, size_t start, size_t end) {
    // Sikrer at start og end er gyldige
    if (start >= string.length || end > string.length || start >= end) {
        fprintf(stderr, "Invali\n");
        exit(EXIT_FAILURE);
    }

    // Opret en ny String struct, der peger på delstrengen
    String substring;
    substring.data = string.data + start; // Justerer pointeren til det nye startpunkt
    substring.length = end - start; // Justerer længden
    substring.owns_data = false; // Ejer ikke strengen
    return substring;
}

int main() {
    // Opretter en String fra en almindelig C-streng
    char original_str[] = "Hello, World!";
    String string = str_construct(original_str);

    // Udtræk en substring fra originalstrengen
    String substring = str_substring(string, 7, 12);

    // Print den oprindelige streng og substring ved hjælp af str_valueOf
    bool is_full_string_allocated = false;
    bool is_sub_string_allocated = false;

    char* full_string = str_valueOf(string, &is_full_string_allocated);
    char* sub_string = str_valueOf(substring, &is_sub_string_allocated);

    printf("Original String: %s\n", full_string);
    printf("Substring: %s\n", sub_string);

    // Frigør allokeret hukommelse
    str_destruct(string); // (owns_data = false)
    str_destruct(substring); // (owns_data = false)

    // Hvis str_valueOf allokerede en ny streng, frigør den
    if (is_full_string_allocated) {
        free(full_string);  // Frigør kun hvis allokeret
    }
    if (is_sub_string_allocated) {
        free(sub_string);   // Frigør kun hvis allokeret
    }

    return 0;
}
