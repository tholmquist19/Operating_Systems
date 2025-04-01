#include <stdio.h>

#include <x86intrin.h> // __builtin_ia32_rdtsc()
#include <time.h> // clock_gettime()
#include <sys/time.h> // clock_getttime()

void measure_gettimeofday(void) {
    struct timezone tz = {0}; // don't really care about what time it actually is...
    struct timeval tv0, tv1;
    gettimeofday(&tv0, &tz);
    gettimeofday(&tv1, &tz);
    printf("Apparent gettimeofday resolution: %ldsec %ldusec \n", tv1.tv_sec - tv0.tv_sec, tv1.tv_usec - tv0.tv_usec);
}

void measure_clock_gettime(void) {
    struct timespec ts0, ts1;
    clock_getres(CLOCK_MONOTONIC_RAW, &ts0);
    printf("Reported clock_gettime resolution: %ldsec %ldnsec \n", ts0.tv_sec, ts0.tv_nsec);

    clock_gettime(CLOCK_MONOTONIC_RAW, &ts0);
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts1);
    printf("Apparent clock_gettime resolution: %ldsec %ldnsec \n", ts1.tv_sec - ts0.tv_sec, ts1.tv_nsec - ts0.tv_nsec);
}

void measure_rdtsc(void) {
    const long unsigned t0 = __builtin_ia32_rdtsc();
    const long unsigned t1 = __builtin_ia32_rdtsc();
    printf("Apparent rdtsc resolution: %ld \"clocks\"??\n", t1 - t0);
}

int main(int argc, char *argv[]) {
    //measure_gettimeofday();
    //measure_clock_gettime();
    measure_rdtsc();
    return 0;
}
