---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 12:32:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 8 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 9 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1770139462 29
1770139467 29
1770139472 29
1770139477 27
1770139482 27
1770139487 27
1770139492 27
1770139497 29
1770139502 29
1770139507 29
1770139512 29
1770139517 29
1770139522 29
1770139527 29
1770139532 29
1770139537 29
1770139542 29
1770139547 29
1770139552 29
1770139557 29
```
</details>

---

