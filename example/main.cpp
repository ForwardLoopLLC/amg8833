#include "amg8833/amg8833.h" //drivers
#include <stdlib.h> // getenv

int main() {
    AMG8833 amg8833(getenv("AMG8833_BUS")[0] - '0');
    if (amg8833.error()) {
        printf("Error: AMG8833 did not initialize\n");
        return 1;
    }
    // reset all registers and settings 
    if(!amg8833.resetInitial()) {
        printf("Error: failed to reset registers\n");
    }
    // turn off moving average mode
    if(!amg8833.setNormalMode()) {
        printf("Error: failed to set normal mode\n");
    }
    // disable interrupt, so the sensor reads the temperature values
    // (instead of triggering an interrupt if the temperature fails below
    // or above a certain threshold)
    if(!amg8833.disableInterrupt()) {
        printf("Error: failed to disable interrupt\n");
    }
    // the sensor will sample ten times per second
    if(!amg8833.setFrameRate10Hz()) {
        printf("Error: failed to set frame rate\n");
    }

    printf("AMG8833 initialized\n");

    // Thermistor (sensor board) temperature
    printf("Thermistor temperature: %f\n", amg8833.thermistorTemperature());

    // Grid temperature for all pixels
    double grid[64];
    printf("Grid Temperature\n");
    amg8833.gridTemperature(grid);
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            printf("%2.6f ", grid[row*col + col]);
        }
        printf("\n");
    }
    printf("AMG8833 installation succeeded.\n");
    return 0;
}
