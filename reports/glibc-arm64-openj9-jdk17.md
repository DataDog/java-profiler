---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-12 04:18:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 8 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1786522410 48
1786522415 48
1786522420 48
1786522425 48
1786522430 48
1786522435 48
1786522440 48
1786522445 48
1786522450 48
1786522455 48
1786522460 48
1786522465 48
1786522470 48
1786522475 36
1786522480 36
1786522485 36
1786522490 36
1786522495 36
1786522500 36
1786522505 36
```
</details>

---

