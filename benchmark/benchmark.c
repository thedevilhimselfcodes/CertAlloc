#include <stdio.h>
#include <stdint.h>
#include <x86intrin.h>
#include "certalloc.h"

/* Serialization macros to prevent CPU instruction reordering */
#define START_CYCLES(start) do { \
    unsigned int dummy; \
    start = __rdtscp(&dummy); \
} while(0)

#define END_CYCLES(end) do { \
    unsigned int dummy; \
    end = __rdtscp(&dummy); \
} while(0)

int main(void) {
    uint64_t start, end;
    uint64_t alloc_cycles, free_cycles;
    
    certalloc_init();
    
    /* Cache warmup */
    void* dummy = cert_alloc(16);
    cert_free(dummy);

    /* Benchmark O(1) Allocation */
    START_CYCLES(start);
    void* ptr = cert_alloc(32);
    END_CYCLES(end);
    alloc_cycles = end - start;

    /* Benchmark O(1) Deallocation */
    START_CYCLES(start);
    cert_free(ptr);
    END_CYCLES(end);
    free_cycles = end - start;

    printf("--- CertAlloc x86 Cycle Benchmarks ---\n");
    printf("Allocation Latency : %llu cycles\n", alloc_cycles);
    printf("Deallocation Latency: %llu cycles\n", free_cycles);
    
    return 0;
}