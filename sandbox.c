// #include <stdio.h>
// #include <regex.h>

// int main(int argc, char const *argv[])
// {
//     regex_t regex;

//     int value = regcomp( &regex, "[:word:]", 0);
//     if (value == 0) {
//         printf("RegEx compiled successfully.\n");
//     } else {
//         printf("Compilation error.\n");
//         exit(0);
//     }

//     char token[10] = ""
//     int result = regexec(&regex, token, 0, NULL, 0);

//     if (result == 0) {
//         printf("Pattern found.\n");
//     }
//     else if (result == REG_NOMATCH) {
//         printf("Pattern not found.\n");
//     }
//     else {
//         printf("An error occurred.\n");
//     }


//     return 0;
// }
