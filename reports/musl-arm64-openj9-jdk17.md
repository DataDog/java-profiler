---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-13 12:35:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 354 |
| Sample Rate | 5.90/sec |
| Health Score | 369% |
| Threads | 12 |
| Allocations | 134 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 12 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 49-54 cores)</summary>

```
1791908952 49
1791908957 49
1791908962 49
1791908967 49
1791908972 49
1791908977 49
1791908982 49
1791908987 49
1791908992 49
1791908997 49
1791909002 49
1791909007 54
1791909012 54
1791909017 54
1791909022 54
1791909027 54
1791909032 54
1791909037 54
1791909042 54
1791909047 54
```
</details>

---

