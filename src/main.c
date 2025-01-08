#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ecl/ecl.h>

int main(int argc, char* argv[]) {
    // Initialize ECL
    cl_boot(argc, argv);
    
    // Setup cleanup on exit
    atexit(cl_shutdown);
    
    char input[1024];
    cl_object result;
    
    printf("ECL REPL (type :quit to exit)\n");
    
    while (1) {
        printf("ecl> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        // Check for quit command
        if (strcmp(input, ":quit\n") == 0) {
            break;
        }
        
        // Create a Lisp string from the input
        cl_object form_string = c_string_to_object(input);
        
        // Read the string as a Lisp form
        cl_object form = cl_read_from_string(1, form_string);
        
        // Evaluate the form
        result = cl_eval(form);
        
        // Print the result
        cl_print(1, result);
        printf("\n");
    }
    
    return 0;
}
