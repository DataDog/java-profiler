# Allocation Pattern Details

## Overview

Allocation sizes are randomized around the configured average to create realistic allocation patterns that better simulate production workloads and increase the probability of hitting various JVM code paths.

## Configuration

Set the average allocation size with `--alloc-size <bytes>` (default: 100,000 bytes = ~100KB)

## Distribution

### Normal Case (95% of allocations)

**Variance Range**: 0.5x to 1.5x average
- Uses `ThreadLocalRandom.nextDouble(0.5, 1.5)` multiplier
- Example with 100KB average:
  - Minimum: 50KB
  - Typical: 75KB - 125KB
  - Maximum: 150KB

### Outliers (5% of allocations)

Split evenly between small and large:

**Small outliers (2.5%)**:
- Range: MIN_SIZE to average/4
- Example with 100KB average: 1KB to 25KB
- Purpose: Test small object allocation paths

**Large outliers (2.5%)**:
- Range: average to min(3x average, MAX_SIZE)
- Example with 100KB average: 100KB to 300KB
- Purpose: Test large object and potential TLAB overflow paths

## Hard Bounds

**Minimum**: 1,024 bytes (1KB)
- Ensures allocations are large enough to be interesting
- Avoids excessive tiny allocations

**Maximum**: 10,000,000 bytes (10MB)
- Prevents OutOfMemoryError
- Keeps allocations reasonable for high-churn scenarios

## Examples

### With default 100KB average:

| Percentile | Approximate Size |
|------------|-----------------|
| 2.5%       | 1KB - 25KB      |
| 25%        | 60KB            |
| 50%        | 100KB           |
| 75%        | 140KB           |
| 97.5%      | 150KB - 300KB   |

### With 1MB average:

| Percentile | Approximate Size |
|------------|-----------------|
| 2.5%       | 1KB - 250KB     |
| 25%        | 600KB           |
| 50%        | 1MB             |
| 75%        | 1.4MB           |
| 97.5%      | 1.5MB - 3MB     |

### With 10KB average:

| Percentile | Approximate Size |
|------------|-----------------|
| 2.5%       | 1KB - 2.5KB     |
| 25%        | 6KB             |
| 50%        | 10KB            |
| 75%        | 14KB            |
| 97.5%      | 15KB - 30KB     |

## Why Randomization?

### 1. TLAB Behavior
- Different sizes exercise different TLAB paths
- Small allocations: fast TLAB allocation
- Large allocations: may trigger TLAB refill or direct allocation
- Very large: always allocated outside TLAB

### 2. JFR Sampling
- JFR's `SetHeapSamplingInterval` uses exponential sampling
- Varied sizes increase chance of hitting sampling points
- Different sizes may trigger different JFR code paths

### 3. Thread Initialization Race
- Different allocation patterns during thread startup
- Variable timing creates different race windows
- Increases probability of hitting the nullptr condition

### 4. Realistic Patterns
- Production workloads have varied allocation sizes
- Single fixed size may not trigger certain edge cases
- Randomization better simulates real-world behavior

## Implementation

Uses `ThreadLocalRandom` for efficient, thread-local random number generation:
- No contention between threads
- Excellent performance characteristics
- Cryptographically unnecessary (perfect for this use case)

## Impact on Reproducer

The randomization:
- ✅ Increases code path coverage
- ✅ Better simulates production conditions
- ✅ Higher probability of race condition
- ✅ Tests multiple allocation sizes per run
- ✅ No performance impact (ThreadLocalRandom is fast)

## Tuning Recommendations

### For Small Object Focus
```bash
--alloc-size 10000  # 10KB average
# Will produce mostly 5KB-15KB, with some 1KB-30KB
```

### For Large Object Focus
```bash
--alloc-size 1000000  # 1MB average
# Will produce mostly 500KB-1.5MB, with some up to 3MB
```

### For TLAB Overflow
```bash
--alloc-size 500000  # 500KB average
# Typical TLAB size is 256KB-512KB, so many allocations will overflow
```

### For Maximum Diversity
Use default 100KB - good balance between small and large allocations.
