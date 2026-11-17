---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 05:51:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 38 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 186 |
| Sample Rate | 3.10/sec |
| Health Score | 194% |
| Threads | 11 |
| Allocations | 134 |

<details>
<summary>CPU Timeline (3 unique values: 38-40 cores)</summary>

```
1794912434 38
1794912439 38
1794912444 38
1794912449 38
1794912454 38
1794912459 38
1794912464 38
1794912469 38
1794912474 38
1794912479 38
1794912484 38
1794912489 38
1794912494 38
1794912499 40
1794912504 40
1794912509 39
1794912514 39
1794912519 39
1794912524 39
1794912529 39
```
</details>

---

