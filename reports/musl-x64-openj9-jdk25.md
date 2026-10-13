---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-13 12:35:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1791908957 89
1791908962 89
1791908967 89
1791908972 89
1791908977 89
1791908982 89
1791908987 89
1791908992 89
1791908997 89
1791909002 89
1791909007 91
1791909012 91
1791909017 91
1791909022 91
1791909027 91
1791909032 91
1791909037 91
1791909042 91
1791909047 91
1791909052 91
```
</details>

---

