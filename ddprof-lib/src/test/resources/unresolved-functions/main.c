#include <stdio.h>

extern int unresolved_symbol;
extern int unresolved_function();

int main() {
    printf("Value of unresolved_symbol: %p\n", &unresolved_symbol);
    printf("Value of unresolved_function: %p\n", &unresolved_function);
    return 0;
}
