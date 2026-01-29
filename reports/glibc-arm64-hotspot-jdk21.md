---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ❌ FAIL

**Date:** 2026-01-29 07:49:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 2.37/sec |
| Health Score | 148% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 10 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 6 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769690794 24
1769690799 24
1769690804 24
1769690809 24
1769690814 24
1769690819 24
1769690824 24
1769690829 24
1769690834 24
1769690839 24
1769690844 24
1769690849 24
1769690854 24
1769690859 24
1769690864 24
1769690869 24
1769690874 24
1769690879 24
1769690884 24
1769690889 24
```
</details>

---

