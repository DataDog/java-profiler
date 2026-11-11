---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:36:29 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 446 |
| Sample Rate | 7.43/sec |
| Health Score | 464% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (4 unique values: 26-32 cores)</summary>

```
1794407531 32
1794407536 32
1794407541 30
1794407546 30
1794407551 30
1794407556 30
1794407561 30
1794407566 30
1794407571 30
1794407576 30
1794407581 30
1794407586 30
1794407591 30
1794407596 30
1794407601 28
1794407606 28
1794407611 28
1794407616 28
1794407621 28
1794407626 28
```
</details>

---

