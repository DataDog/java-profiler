---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-21 01:05:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1792558796 14
1792558801 14
1792558806 14
1792558811 14
1792558816 14
1792558821 14
1792558826 14
1792558831 14
1792558836 14
1792558841 14
1792558846 14
1792558851 34
1792558856 34
1792558861 34
1792558866 34
1792558871 34
1792558876 34
1792558881 34
1792558886 34
1792558891 34
```
</details>

---

