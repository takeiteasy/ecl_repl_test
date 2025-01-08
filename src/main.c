#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ecl/ecl.h>

int main(int argc, char* argv[]) {
    cl_boot(argc, argv);
    atexit(cl_shutdown);
#define INPUT_SIZE 1024
    char input[INPUT_SIZE];
    int cursor = 0;
    cl_object result;
    printf("$ ");
    for (;;) {
        int c = 0;
        while (c != EOF && c != '\n') {
            if (cursor >= INPUT_SIZE)
                cursor = INPUT_SIZE - 1;
            switch ((c = getchar())) {
                case EOF:
                case '\n':
                    input[cursor] = '\0';
                    break;
                default:
                    input[cursor++] = c;
                    if (cursor >= INPUT_SIZE) {
                        input[cursor-1] = '\0';
                        c = EOF;
                    }
                    break;
            }
        }
        if (!cursor)
            goto BAIL;
        int anything = 0;
        for (const char *p = input; *p; p++)
            if (*p != ' ') {
                anything = 1;
                break;
            }
        if (!anything)
            goto BAIL;
        
        if (!strcmp(input, ":quit"))
            break;
        cl_object form = c_string_to_object((const char*)input);
        result = cl_eval(form);
        cl_print(1, result);
        printf("\n");
    BAIL:
        memset(input, 0, INPUT_SIZE * sizeof(char));
        cursor = 0;
        printf("$ ");
    }
    return 0;
}
