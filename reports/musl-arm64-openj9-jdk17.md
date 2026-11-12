---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 18:03:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 30 |
| Sample Rate | 0.50/sec |
| Health Score | 31% |
| Threads | 9 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (2 unique values: 32-44 cores)</summary>

```
1794524351 32
1794524356 32
1794524361 32
1794524366 32
1794524371 32
1794524376 32
1794524381 32
1794524386 32
1794524391 32
1794524396 32
1794524401 32
1794524407 32
1794524412 32
1794524417 32
1794524422 32
1794524427 32
1794524432 32
1794524437 32
1794524442 32
1794524447 32
```
</details>

---

