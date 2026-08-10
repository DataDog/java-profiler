---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-10 11:46:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 909 |
| Sample Rate | 15.15/sec |
| Health Score | 947% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (4 unique values: 76-88 cores)</summary>

```
1786376356 86
1786376361 86
1786376366 86
1786376371 86
1786376376 86
1786376381 84
1786376386 84
1786376391 84
1786376396 84
1786376401 84
1786376406 86
1786376411 86
1786376416 86
1786376421 86
1786376426 88
1786376431 88
1786376436 76
1786376441 76
1786376446 76
1786376451 76
```
</details>

---

