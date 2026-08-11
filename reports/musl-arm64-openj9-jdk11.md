---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 11:57:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 270 |
| Sample Rate | 4.50/sec |
| Health Score | 281% |
| Threads | 11 |
| Allocations | 182 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (4 unique values: 10-53 cores)</summary>

```
1786463503 10
1786463508 10
1786463513 10
1786463518 10
1786463523 10
1786463528 10
1786463533 44
1786463538 44
1786463543 33
1786463548 33
1786463553 33
1786463558 33
1786463563 33
1786463568 33
1786463573 33
1786463578 33
1786463583 33
1786463588 33
1786463593 33
1786463598 33
```
</details>

---

