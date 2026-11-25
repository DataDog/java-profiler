---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 14:23:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (5 unique values: 76-88 cores)</summary>

```
1795634330 88
1795634335 79
1795634340 79
1795634346 79
1795634351 79
1795634356 80
1795634361 80
1795634366 80
1795634371 78
1795634376 78
1795634381 76
1795634386 76
1795634391 76
1795634396 76
1795634401 76
1795634406 76
1795634411 76
1795634416 76
1795634421 78
1795634426 78
```
</details>

---

