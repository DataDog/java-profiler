---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 07:26:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 10 |
| Allocations | 544 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1795177351 32
1795177356 32
1795177361 32
1795177366 32
1795177371 32
1795177376 32
1795177381 32
1795177386 32
1795177391 32
1795177396 32
1795177401 32
1795177406 32
1795177411 32
1795177416 32
1795177421 32
1795177426 32
1795177431 32
1795177436 32
1795177441 32
1795177446 27
```
</details>

---

