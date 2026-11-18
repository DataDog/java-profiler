---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 06:08:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 36-45 cores)</summary>

```
1794999779 36
1794999784 36
1794999789 36
1794999794 36
1794999799 36
1794999804 36
1794999809 36
1794999814 36
1794999819 36
1794999824 36
1794999829 36
1794999834 36
1794999839 36
1794999844 36
1794999849 36
1794999854 45
1794999859 45
1794999864 45
1794999869 45
1794999874 45
```
</details>

---

