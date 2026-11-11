---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 15:42:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 10 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (4 unique values: 52-65 cores)</summary>

```
1794429418 57
1794429423 52
1794429428 52
1794429433 52
1794429438 52
1794429443 52
1794429448 52
1794429453 52
1794429458 52
1794429463 52
1794429468 52
1794429473 52
1794429478 52
1794429483 52
1794429488 52
1794429493 52
1794429499 52
1794429504 52
1794429509 52
1794429514 54
```
</details>

---

