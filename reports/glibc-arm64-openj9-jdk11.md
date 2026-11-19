---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 05:58:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 227 |
| Sample Rate | 3.78/sec |
| Health Score | 236% |
| Threads | 12 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (6 unique values: 29-46 cores)</summary>

```
1795085562 29
1795085567 29
1795085572 29
1795085577 29
1795085582 29
1795085587 30
1795085592 30
1795085597 30
1795085602 30
1795085607 30
1795085612 30
1795085617 30
1795085622 44
1795085627 44
1795085632 46
1795085637 46
1795085642 43
1795085647 43
1795085652 43
1795085657 43
```
</details>

---

