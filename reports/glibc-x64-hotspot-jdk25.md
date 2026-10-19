---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-19 06:50:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 9 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (3 unique values: 24-29 cores)</summary>

```
1792406788 29
1792406793 29
1792406798 29
1792406803 29
1792406808 29
1792406813 29
1792406818 29
1792406823 27
1792406828 27
1792406833 27
1792406838 27
1792406843 27
1792406848 27
1792406853 27
1792406858 27
1792406863 27
1792406868 27
1792406873 27
1792406878 27
1792406883 29
```
</details>

---

