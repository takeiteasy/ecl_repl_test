#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ecl/ecl.h>

static int mute_stdout(void) {
    int original_stdout = dup(STDOUT_FILENO);
    int dev_null = open("/dev/null", O_WRONLY);
    dup2(dev_null, STDOUT_FILENO);
    close(dev_null);
    return original_stdout;
}

static void restore_stdout(int original_stdout) {
    dup2(original_stdout, STDOUT_FILENO);
    close(original_stdout);
}

#ifdef SILENCE_TURTLE
#define CL_EVAL(...) \
    do { \
        int o = mute_stdout(); \
        result = cl_eval(__VA_ARGS__); \
        restore_stdout(o); \
    } while(0)
#else
#define CL_EVAL(...) (result = cl_eval(__VA_ARGS__))
#endif

int main(int argc, char* argv[]) {
    cl_boot(argc, argv);
    atexit(cl_shutdown);
    
    cl_object result;
    CL_EVAL(c_string_to_object("(require 'asdf)"));
    CL_EVAL(c_string_to_object("(load \"turtle.asd\")"));

#define INPUT_SIZE 1024
    char input[INPUT_SIZE];
    int cursor = 0;
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
        CL_EVAL(c_string_to_object((const char*)input));
        cl_print(1, result);
        printf("\n");
    BAIL:
        memset(input, 0, INPUT_SIZE * sizeof(char));
        cursor = 0;
        printf("$ ");
    }
    return 0;
}
