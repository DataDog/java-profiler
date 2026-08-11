---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-11 11:57:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 826 |
| Sample Rate | 13.77/sec |
| Health Score | 861% |
| Threads | 12 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1786463518 24
1786463523 24
1786463528 24
1786463533 24
1786463538 24
1786463543 29
1786463548 29
1786463553 29
1786463558 29
1786463563 29
1786463568 29
1786463573 29
1786463578 29
1786463583 29
1786463588 29
1786463593 29
1786463598 29
1786463603 29
1786463608 29
1786463613 29
```
</details>

---

