---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 03:00:21 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 11 |
| Allocations | 35 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 170 |
| Sample Rate | 2.83/sec |
| Health Score | 177% |
| Threads | 11 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (4 unique values: 27-48 cores)</summary>

```
1794988444 28
1794988449 28
1794988454 28
1794988459 28
1794988464 28
1794988469 28
1794988474 28
1794988479 27
1794988484 27
1794988489 27
1794988494 27
1794988499 27
1794988504 27
1794988509 27
1794988514 27
1794988519 47
1794988524 47
1794988529 47
1794988534 48
1794988539 48
```
</details>

---

