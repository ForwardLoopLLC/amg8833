#include "amg8833/amg8833.h"

int main() {
    AMG8833 amg8833(0);
    if (amg8833.error()) {
        printf("Error: AMG8833 did not initialize\n");
        return 1;
    }
    amg8833.setNormalMode();
    amg8833.resetInitial();
    amg8833.disableInterrupt();
    amg8833.setFrameRate10Hz();
    printf("AMG8833 initialized\n");
    printf("Thermistor temperature: %f\n", amg8833.thermistorTemperature());
    double grid[64];
    for (int iter = 0; iter < 5; iter++) {
        printf("Grid Temperature (%d):\n", iter);
        amg8833.gridTemperature(grid);
        amg8833.wait(100000);
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                printf("%2.6f ", grid[row*col + col]);
            }
            printf("\n");
        }
    }
    return 0;
}
