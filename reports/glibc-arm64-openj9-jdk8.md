---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-10 05:51:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1791625610 32
1791625615 32
1791625620 32
1791625625 32
1791625630 32
1791625635 32
1791625640 32
1791625645 32
1791625650 32
1791625655 32
1791625660 32
1791625665 32
1791625670 32
1791625675 32
1791625680 32
1791625685 32
1791625690 32
1791625695 32
1791625700 32
1791625705 32
```
</details>

---

