#include "amg8833/amg8833.h"

int main() {
    AMG8833 amg8833(0);
    if (amg8833.error()) {
        printf("Error: AMG8833 did not initialize\n");
        return 1;
    }
    printf("AMG8833 initialized\n");
    return 0;
}
