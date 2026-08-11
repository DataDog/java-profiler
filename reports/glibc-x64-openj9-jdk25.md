---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-11 09:28:00 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (3 unique values: 85-89 cores)</summary>

```
1786454456 89
1786454461 89
1786454466 89
1786454472 89
1786454477 89
1786454482 89
1786454487 89
1786454492 89
1786454497 89
1786454502 89
1786454507 89
1786454512 89
1786454517 89
1786454522 89
1786454527 87
1786454532 87
1786454537 87
1786454542 87
1786454547 87
1786454552 87
```
</details>

---

