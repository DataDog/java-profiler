---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-09 05:55:02 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 949 |
| Sample Rate | 15.82/sec |
| Health Score | 989% |
| Threads | 9 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791539350 48
1791539355 48
1791539360 43
1791539365 43
1791539370 43
1791539375 43
1791539380 43
1791539385 43
1791539390 43
1791539395 43
1791539400 43
1791539405 43
1791539410 43
1791539415 43
1791539420 43
1791539425 43
1791539430 43
1791539435 43
1791539440 43
1791539445 43
```
</details>

---

