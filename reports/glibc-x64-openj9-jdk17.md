---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-11 10:07:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 934 |
| Sample Rate | 15.57/sec |
| Health Score | 973% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1773237496 32
1773237501 32
1773237506 32
1773237511 32
1773237516 32
1773237521 32
1773237526 32
1773237531 32
1773237536 32
1773237541 32
1773237546 30
1773237551 30
1773237556 30
1773237561 30
1773237566 30
1773237571 30
1773237576 30
1773237581 30
1773237586 28
1773237591 28
```
</details>

---

