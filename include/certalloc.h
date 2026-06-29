/**
 * certalloc.h - Deterministic memory allocator for safety-critical systems
 * * MISRA C:2012 compliant (with minimal deviations noted)
 * Copyright (C) 2025-2026 CertAlloc Project
 */

#ifndef CERTALLOC_H
#define CERTALLOC_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Maximum number of memory pools supported
 * Increase if your application needs more pool types
 */
#define CERTALLOC_MAX_POOLS 16

/**
 * @brief Memory pool descriptor
 * * Each pool manages fixed-size blocks. All pools are statically allocated
 * at compile time based on static analysis results.
 */
typedef struct {
    uint32_t block_size;     /**< Size of each block in bytes */
    uint32_t num_blocks;     /**< Total number of blocks in this pool */
    uint32_t free_blocks;    /**< Current number of free blocks */
    void* pool_memory;    /**< Pointer to pool memory region */
    uint32_t* free_bitmap;   /**< Bitmap of free blocks (1=free, 0=allocated) */
    uint32_t bitmap_words;   /**< Number of 32-bit words in bitmap */
} certalloc_pool_t;

/**
 * @brief Allocator statistics
 */
typedef struct {
    uint32_t total_allocations;   /**< Total allocations ever performed */
    uint32_t total_frees;         /**< Total frees ever performed */
    uint32_t allocation_failures; /**< Number of failed allocations */
    uint32_t max_alloc_time_us;   /**< Maximum allocation time in microseconds */
    uint32_t min_alloc_time_us;   /**< Minimum allocation time in microseconds */
    uint32_t total_alloc_time_us; /**< Sum of all allocation times */
} certalloc_stats_t;

/**
 * @brief Initialize the allocator
 * * Must be called once before any allocations. Initializes all pools
 * and sets up free bitmaps.
 * * @return true if initialization succeeded, false otherwise
 */
bool certalloc_init(void);

/**
 * @brief Allocate memory from the appropriate pool
 * * O(1) constant-time allocation. Uses the pool whose block_size is
 * the smallest that can accommodate the requested size.
 * * @param size Number of bytes to allocate
 * @return Pointer to allocated memory, or NULL if no suitable pool
 */
void* cert_alloc(size_t size);

/**
 * @brief Free memory back to its pool
 * * O(1) constant-time deallocation. The pointer must have been returned
 * by cert_alloc and must not be freed twice.
 * * @param ptr Pointer to memory to free
 */
void cert_free(void* ptr);

/**
 * @brief Get allocator statistics
 * * @return Pointer to constant statistics structure
 */
const certalloc_stats_t* certalloc_get_stats(void);

/**
 * @brief Get pool information for a specific pool index
 * * @param pool_index Pool index (0 to CERTALLOC_MAX_POOLS-1)
 * @return Pointer to pool structure, or NULL if invalid index
 */
const certalloc_pool_t* certalloc_get_pool(uint32_t pool_index);

/**
 * @brief Get total memory used by allocator
 * * @return Total bytes of memory consumed by all pools
 */
uint32_t certalloc_get_total_memory(void);

/**
 * @brief Get memory utilization percentage
 * * @return Utilization percentage (0-100)
 */
uint8_t certalloc_get_utilization_percent(void);

/* ========================================================================== */
/* Concurrency Hooks - User must implement these in their application code    */
/* ========================================================================== */

/**
 * @brief Enter critical section (disable interrupts / acquire mutex)
 */
extern void certalloc_enter_critical(void);

/**
 * @brief Exit critical section (enable interrupts / release mutex)
 */
extern void certalloc_exit_critical(void);

#ifdef __cplusplus
}
#endif

#endif /* CERTALLOC_H */