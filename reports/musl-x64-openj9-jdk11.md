---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-06 05:14:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 8 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1770372562 27
1770372567 27
1770372572 27
1770372577 27
1770372582 27
1770372587 27
1770372592 27
1770372597 27
1770372602 27
1770372607 32
1770372612 32
1770372617 32
1770372622 32
1770372627 32
1770372632 32
1770372637 32
1770372642 32
1770372647 32
1770372652 32
1770372657 32
```
</details>

---

