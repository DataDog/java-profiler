---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-13 01:03:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 170 |
| Sample Rate | 2.83/sec |
| Health Score | 177% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 35-41 cores)</summary>

```
1791867570 41
1791867575 41
1791867580 41
1791867585 41
1791867590 41
1791867595 41
1791867600 41
1791867605 39
1791867610 39
1791867615 39
1791867620 39
1791867625 39
1791867630 39
1791867635 39
1791867640 39
1791867645 37
1791867650 37
1791867655 35
1791867660 35
1791867665 35
```
</details>

---

