#include "amg8833/amg8833.h"
#include <stdio.h>
#include <sys/time.h>

double time() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return (double) tp.tv_sec + tp.tv_usec/1000000.0;
}

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
    while(true) {
        double thermTemp = amg8833.thermistorTemperature();
        amg8833.gridTemperature(grid);
        amg8833.wait(100000);
        char data[7*8*8], *pos = data;
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                pos += sprintf(pos, "%02.3f ", grid[row*col + col]);
            }
            pos += sprintf(pos, "\n");
        }
        FILE* fid = fopen("/amg8833/data/data", "w");
        fprintf(fid,
                "%.1f,%02.3f,\n%s\n",
                time(),
                thermTemp,
                data);
        fflush(fid);
        fclose(fid);
    }
    return 0;
}
