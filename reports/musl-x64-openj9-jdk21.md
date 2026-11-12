---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 13:21:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (6 unique values: 67-76 cores)</summary>

```
1794507331 69
1794507336 69
1794507341 69
1794507346 69
1794507351 69
1794507356 67
1794507361 67
1794507366 67
1794507371 72
1794507376 72
1794507381 76
1794507386 76
1794507391 76
1794507396 74
1794507401 74
1794507406 74
1794507411 74
1794507416 73
1794507421 73
1794507426 73
```
</details>

---

